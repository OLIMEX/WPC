/**
 * Olimex WPC#46: Clock arrows
 *
 * Clock minute and hour arrows cross as they revolve around.
 * Make code that compute how many times the arrows cross in one twelve hour period, and print list of those times.
 *
 * License: LGPL
 * Compile: gcc -o clock_arrows clock_arrows.c
 *
 * @author gobpuH
 * @date Fri Mar 14 23:25:30 EET 2014
 */

#include <stdio.h>	// printf
#include <stdint.h>	// uint16_t

/**
 * @brief Clock related constants
 */
#define HOURS		12
#define MIN_PER_HOUR	60
#define SEC_PER_MIN	60
#define MS_PER_SEC	1000
#define REV_IN_DEG	360
#define HOUR_IN_DEG	((REV_IN_DEG)/(HOURS))
#define MIN_IN_DEG	((REV_IN_DEG)/(MIN_PER_HOUR))

/**
 * Common sense dictate that arrows will overlap once per hour or less :-)
 * That's why it's enough to check overlap position for each hour.
 * Here is the relationship between positions of both arrows:
 * hour * HOUR_IN_DEG + (float)min / MIN_PER_HOUR * HOUR_IN_DEG = min * MIN_IN_DEG, where
 * hour is known and take value in range [0..11].
 */
int main(void)
{
	uint8_t i, j = 0;

	printf(" # |   Cross @   \n");
	printf("---+-------------\n");
	for(i=0;i<HOURS;i++) {
		float cross = i * HOUR_IN_DEG / (MIN_IN_DEG - 1.f/ MIN_PER_HOUR * HOUR_IN_DEG);
		// convert float minutes to Min:Sec.Millis format
		uint8_t m = (uint8_t)cross;		// minutes
		if (m >= MIN_PER_HOUR)			// make sure that m is in range [0..59]
			continue;
		cross -= m;
		cross *= SEC_PER_MIN;
		uint8_t s = (uint8_t)cross;		// seconds
		cross -= s;
		cross *= MS_PER_SEC;
		cross += .5f;				// round up
		uint16_t ms = (uint16_t)cross;		// milliseconds
		printf("%02d | %02dH%02dM%02d.%03d\n", ++j, i, m, s, ms);
	}
}
