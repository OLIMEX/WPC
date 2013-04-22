#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <math.h>
#include <unistd.h>
#include "ss.h"

#define WRITE(offset, value)	(*(volatile uint32_t*)(addr+(offset))) = (value)
#define READ(offset)		(*(volatile uint32_t*)(addr+(offset)))

#define ERROR(str)		do { perror(str); exit(255); } while(0)

/* Helper function to map SS memory */
void *mapmem(void)
{
	int fd;
	void *addr;

	fd = open("/dev/mem", O_RDWR | O_SYNC);
	if (fd == -1)
		ERROR("open");

	addr = mmap(0, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x01C15000);
	if (addr == MAP_FAILED)
		ERROR("mmap");

	return addr;
}

/* Helper function to enable/disable SS clocks */
void setclock(int state)
{
	int fd;
	void *addr;
	uint32_t clk;

	fd = open("/dev/mem", O_RDWR | O_SYNC);
	if (fd == -1)
		ERROR("open");

	addr = mmap(0, 0x200, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x01C20000);
	if (addr == MAP_FAILED)
		ERROR("mmap");

	clk = READ(0x60);
	clk &= ~(1 << 5);
	clk |= (state << 5);
	WRITE(0x60, clk);

	clk = 0;
	clk |= (state << 31);
	clk |= (1 << 24); // PLL6
	clk |= (1 << 16); // PLL6/(2^1)/(2+1)
	clk |= (2 << 0);
	WRITE(0x9C, clk);

	munmap(addr, 0x200);
	close(fd);
}

void seed(void *addr, uint32_t seed[6])
{
	WRITE(SUNXI_SS_KEY0, seed[0]);
	WRITE(SUNXI_SS_KEY1, seed[1]);
	WRITE(SUNXI_SS_KEY2, seed[2]);
	WRITE(SUNXI_SS_KEY3, seed[3]);
	WRITE(SUNXI_SS_KEY4, seed[4]);
	WRITE(SUNXI_SS_KEY5, seed[5]);
}

uint32_t needle_across = 0;
uint32_t needle_total = 0;
double stripe = 6.0;
double needle = 5.0;
double halfneedle = 2.5;

/* This function checks if a needle at dist from the line from its central
 * point and with angle will be across it or not */
void simulate_short_needle(double dist, double angle)
{
	if (dist == 0 || dist <=  halfneedle * sin(angle))
		needle_across++;
}

/* This calculates our pi approximation based on the needle counts, stripe size
 * and needle length */
void approximate_pi(void)
{
	double pi = (2.0 * needle * needle_total) / (stripe * needle_across);

	printf("PI is approximately %f (%d/%d across)\n", pi, needle_across, needle_total);
}

int main(int argc, char *argv[])
{
	void *addr;
	unsigned int available = 0, i, nruns;
	double len, angle;
	uint32_t flags = 0, tmp;
	uint32_t seedval[6] = {0xcdecfa8b, 0x0fa57e41, 0x13cee177,
			       0xa85faf2d, 0xe9f873fd, 0xad5103ef};

	if (argc < 4) {
		fprintf(stderr, "Usage: %s <needle length> <stripe length> <runs>\n", argv[0]);
		return 0;
	}

	sscanf(argv[1], "%lf", &needle);
	sscanf(argv[2], "%lf", &stripe);
	sscanf(argv[3], "%u", &nruns);
	halfneedle = needle / 2.0;
	needle_total = nruns;

	if (needle >= stripe) {
		fprintf(stderr, "Long needle case not supported\n");
		return 0;
	}

	printf("Simulating %u runs with needles of length %.2f and stripes of length %.2f\n",
	       nruns, needle, stripe);

	/* Enable SS clock*/
	setclock(1);

	/* Map SS memory space */
	addr = mapmem();

	/* seed PRNG */
	seed(addr, seedval);

	/* Configure SS for PRNG */
	flags |= SUNXI_SS_ENABLED;
	flags |= SUNXI_OP_PRNG;
	flags |= SUNXI_PRNG_CONTINUE;
	WRITE(SUNXI_SS_CTL, flags);

	/* Launch a simulation per 32 bits of pseudo-randomness read */
	for (i=0; i <= nruns; i++) {
		if (available) {
			tmp = READ(SUNXI_SS_TXFIFO);
			len = (tmp >> 16) * stripe / 131070.0;
			angle = (tmp & 0xffff) * M_PI_2 / 65535.0;
			simulate_short_needle(len, angle);
		} else {
			while (!((tmp=READ(SUNXI_SS_FCSR)) & SUNXI_TXFIFO_AVAILABLE))
				;
			available = SUNXI_TXFIFO_SPACES(tmp);
		}
	}

	approximate_pi();

	/* Shut it down */
	WRITE(SUNXI_SS_CTL, 0);
	setclock(0);

	return 0;
}
