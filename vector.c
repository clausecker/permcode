#include <string.h>
#include "permcode.h"

/* use a 128 bit vector of 5 bit numbers */
const char *algname = "vector";
typedef unsigned __int128 uint128;

extern void encode(unsigned char perm[PC_COUNT])
{
	size_t i, j;
	int count;
	uint128 occupation = (uint128)1782769360921721754ULL << 64 | 14242959524133701664ULL;

	for (i = 0; i < PC_COUNT; i++) {
		occupation -= ((uint128)74382032555280450ULL << 64 | 1190112520884487200ULL) << 5 * perm[i];
		perm[i] = 31 & occupation >> 5 * perm[i];
	}
}

extern void decode(unsigned char perm[PC_COUNT])
{
	size_t i, j;
	int count;
	uint128 occupation = (uint128)1782769360921721754ULL << 64 | 14242959524133701664ULL, mask;

	for (i = 0; i < PC_COUNT; i++) {
		mask = ((uint128)1 << 5 * perm[i]) - 1;
		perm[i] = 31 & occupation >> 5 * perm[i];
		occupation = (occupation & mask) | (occupation >> 5 & ~mask);
	}
}
