#include <string.h>
#include "permcode.h"

/* use a 64 bit vector of 4 bit numbers */
const char *algname = "vector";

extern void encode(unsigned char perm[PC_COUNT])
{
	size_t i, j;
	int count;
	unsigned long long occupation = 0xfedcba9876543210ull;

	for (i = 0; i < PC_COUNT; i++) {
		occupation -= 0x1111111111111110ull << 4 * perm[i];
		perm[i] = 15 & occupation >> 4 * perm[i];
	}
}

extern void decode(unsigned char perm[PC_COUNT])
{
	size_t i, j;
	int count;
	unsigned long long occupation = 0xfedcba9876543210ull, mask;

	for (i = 0; i < PC_COUNT; i++) {
		mask = (1ull << 4 * perm[i]) - 1;
		perm[i] = 15 & occupation >> 4 * perm[i];
		occupation = (occupation & mask) | (occupation >> 4 & ~mask);
	}
}
