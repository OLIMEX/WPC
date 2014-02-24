/**
 * Olimex WPC#44: ECG heart beat detection.
 *
 * Make code which detect the heart rate using raw signal info.
 * Signal data and packet structure are available at
 * https://github.com/OLIMEX/WPC/tree/master/ISSUE-44
 *
 * License: LGPL
 * Compile: gcc -o heart_rate heart_rate.c
 *
 * @author gobpuH
 * @date Sat Feb 22 08:42:48 EET 2014
 */

#include <stdio.h>	// printf
#include <stdint.h>	// uint16_t
#include <unistd.h>	// sysconf
#include <sys/types.h>	// struct stat
#include <sys/stat.h>	// stat
#include <fcntl.h>
#include <sys/mman.h>	// mmap
#include <stdlib.h>	// calloc
#include <errno.h>	// errno

/**
 * @brief EEG measurement parameters
 */
#define EEG_SAMPLING_FREQUENCY		256
#define EEG_ABS_MAX			1023	// 10bit
#define EEG_ABS_MIN			0

/**
 * @brief Heart rate measurement settings
 */
#define EEG_GLOBAL_EXTREMUM_THREASHOLD	16	// 4 LSB
#define EEG_TRANSITION_DURATION_MS	50	// [ms]
#define EEG_TRANSITION_DURATION		(EEG_SAMPLING_FREQUENCY * EEG_TRANSITION_DURATION_MS / 1000)	// [sample periods]
/**
 * @brief The middle of the range is good detection level.
 */
#define EEG_TRANSITION_DETECTION_LEVEL	((EEG_ABS_MAX - EEG_ABS_MIN) / 2)
#define TRANSITION_SIZE			5	// make sure that TRANSITION_SIZE is in range [EEG_ABS_MIN + EEG_GLOBAL_EXTREMUM_THREASHOLD, EEG_ABS_MAX - EEG_GLOBAL_EXTREMUM_THREASHOLD]

/**
 * @brief Generic utils
 */
#define swap_bytes(w)	((w).byte[0]<<8 | (w).byte[1])
#define ascii2nibble(a)	(isalpha((a)) ? ((a) - 'A' + 10) : ((a) - '0'))

typedef union word_union {
	uint16_t word;
	struct {
		uint8_t byte[2];
	};
} word_t;

typedef struct modeeg_packet
{
	uint8_t		sync0;		// = 0xA5
	uint8_t		sync1;		// = 0x5A
	uint8_t		version;	// = 2
	uint8_t		count;		// packet counter. Increases by 1 each packet.
	word_t		data[6];	// 10-bit sample (= 0 - 1023) in big endian (Motorola) format.
	uint8_t		switches;	// State of PD5 to PD2, in bits 3 to 0.
} __attribute__((packed)) eeg_t;

int main(void)
{
	uint16_t i;
	char *file = "ECGSAMPLE.txt";	// file name
	int fd;				// file descriptor
	char *data;			// ascii data
	struct stat f_stat;		// file stat
	size_t file_size;		// file size in bytes
	size_t mm_size;			// memory map in bytes
	size_t sample_num;		// number of samples (each sample have 6 data channels)
	eeg_t *sample;			// binary data
	uint8_t *sample_data;		// "raw" binary data
	float transition[TRANSITION_SIZE] = {[0 ... TRANSITION_SIZE-1] = 0.f};	// make it simple - dynamic allocation is not interesting, heart rate will be calculated over first TRANSITION_SIZE transitions
	uint8_t transition_num;		// number of found transitions

	/**
	 * @brief State machine looking for MAX to MIN transitions
	 *
	 * Actual search start when value is MAX proximity.
	 * Second step is to find local extremum. After that cross point between EEG data and EEG_TRANSITION_DETECTION_LEVEL is calculated and stored as result.
	 * These cross points will be used later for heart rate calculation.
	 * Finally transition is validated by MIN in following EEG_TRANSITION_DURATION samples.
	 *
	 * @param [in] time
	 * @param [in] value
	 * @return number of transitions, limited by TRANSITION_SIZE value
	 */
	uint8_t find_transition(uint16_t time, uint16_t value)
	{
		enum {
			HIGH = 0,
			MAXIMUM,
			TRANSITION,
			MINIMUM,
			STATE_NUM
		};
		static uint8_t index = 0;	// transition index
		static uint8_t state = 0;	// keeps track of search progress
		static uint16_t old;		// old value
		static uint16_t start;		// time of maximum - start moment for transition hunt

		if (index >= TRANSITION_SIZE) {
			return(index);
		}
		switch (state) {
		case HIGH:
			if (value >= EEG_ABS_MAX - EEG_GLOBAL_EXTREMUM_THREASHOLD) {
				old = value;
				state++;
			}
			break;
		case MAXIMUM:
			if (value < old) {
				start = time - 1;	// previous time value
				state++;
			}
			old = value;
			break;
		case TRANSITION:
			if (time - start > EEG_TRANSITION_DURATION) {	// times up, start all over again
				state = 0;
				break;
			}
			if (value < EEG_TRANSITION_DETECTION_LEVEL) {
				transition[index++] = (float)time - ((float)(EEG_ABS_MAX/2 - value))/(old - value);
				state++;
			}
			old = value;
			break;
		case MINIMUM:
			if (time - start > EEG_TRANSITION_DURATION) {	// times up, remove false transition and start all over again
				state = 0;
				transition[--index] = 0.f;		// remove false positive
				break;
			}
			if (value <= EEG_ABS_MIN + EEG_GLOBAL_EXTREMUM_THREASHOLD) {
				state++;
				state %= STATE_NUM;
			}
			break;
		}
		return(index);
	}

	size_t page_size = (size_t)sysconf(_SC_PAGESIZE);
	if (-1 == stat(file, &f_stat)) {
		printf("Err: %s (%s)\n", strerror(errno), file);
		return(errno);
	}
	file_size = f_stat.st_size;

	mm_size = (f_stat.st_size-1)/page_size + 1;	// round up mmap size in number of pages
	mm_size *= page_size;				// mmap size in bytes
	fd = open(file, O_RDONLY);
	if (-1 == fd) {
		printf("Err: %s (%s)\n", strerror(errno), file);
		return(errno);
	}
	data = mmap(NULL, mm_size, PROT_READ, MAP_SHARED, fd, 0);
	if (MAP_FAILED == data) {
		printf("Err: %s\n", strerror(errno));
		close(fd);
		return(errno);
	}

	sample_num = file_size / (2 * sizeof(eeg_t));	/// @note each byte is represented by 2 characters
	sample = calloc(sample_num, sizeof(eeg_t));
	if (NULL == sample) {
		printf("Err: %s\n", strerror(ENOMEM));
		munmap(data, mm_size);
		close(fd);
		return(ENOMEM);
	}
	sample_data = (uint8_t *)(void *)sample;

	/**
	 * Convert data array from ASCII to binary.
	 */
	for(i=0;i<file_size/2;i++) {
		sample_data[i] = ascii2nibble(data[2*i+0])<<4 | ascii2nibble(data[2*i+1]);
	}

	/**
	 * Find MAX to MIN transitions.
	 *
	 * @note Actual data is stored in first channel, no need to check all channels.
	 */
	for(i=0;i<sample_num;i++) {
		transition_num = find_transition(i, swap_bytes(sample[i].data[0]));
	}

	/**
	 * Show results.
	 *
	 * @note At least two transitions are needed in order to calculate heart rate at all.
	 */
	if (transition_num > 1) {
		float avg = 0.f;
		printf(" # |\t\theart rate\n");
		printf("   |\t[1/min]\t\t[Hz]\n");
		printf("---+--------------------------\n");
		for(i=1;i<transition_num;i++) {
			float hr = 256.f/(transition[i] - transition[i-1]);
			avg += hr;
			printf("%2d |\t%7.3f\t\t%6.4f\n", i, 60.f*hr, hr);
		}
		avg /= (float)(transition_num-1);
		printf("---+--------------------------\n");
		printf("Avg|\t%7.3f\t\t%6.4f\n", 60.f*avg, avg);
	} else {
		printf("Unable to measure the heart rate\n");
	}

	/**
	 * Clean up
	 */
	if (sample) {
		free(sample);
		sample = NULL;
	}
	munmap(data, mm_size);
	close(fd);
}
