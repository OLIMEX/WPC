#include <stdio.h>
#include <stdint.h>

/* xor shift PRNG
 * http://xorshift.di.unimi.it/
 * to perform dieharder testing
 * sudo yum install dieharder
 * ./a.out | dieharder -g 200 -d 205 
 */
uint64_t s[2];

uint64_t murmurhash3(uint64_t x) {
	x ^= x >> 33;
	x *= 0xff51afd7ed558ccdULL;
	x ^= x >> 33;
	x *= 0xc4ceb9fe1a85ec53ULL;
	return x ^= x >> 33;
}

uint64_t next_xorshift128plus(void) { 
	uint64_t s1 = s[0];
	const uint64_t s0 = s[1];
	s[0] = s0;
	s1 ^= s1 << 24; //changed from 23 to 24 
	return (s[1] = ( s1 ^ s0 ^ ( s1 >> 17 ) ^ ( s0 >> 26 ) )) + s0;
}

void main() {
	uint64_t r;
        const uint64_t seed = 0x5a1a51a5;
	s[0] = murmurhash3(seed);
	s[1] = murmurhash3(s[0]);
	for (;;)
	{
		r = next_xorshift128plus();
		fwrite(&r, sizeof(uint64_t), 1, stdout);
	}
}

