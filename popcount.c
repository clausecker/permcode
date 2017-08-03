#include <string.h>
#include "permcode.h"

/* count places to the left with popcount */
const char *algname = "popcount";

extern void encode(unsigned char perm[PC_COUNT])
{
	size_t i, j;
	int count;
	unsigned occupation = (1 << SQ_COUNT) - 1;

	for (i = 0; i < PC_COUNT; i++) {
		count = __builtin_popcount(occupation & (1 << perm[i]) - 1);
		occupation &= ~(1 << perm[i]);
		perm[i] = count;
	}
}

extern void decode(unsigned char perm[PC_COUNT])
{
	size_t i, j;
	int count;
	unsigned occupation = (1 << SQ_COUNT) - 1;

	for (i = 0; i < PC_COUNT; i++) {
		count = 0;
		for (j = 0; count <= perm[i]; j++)
			count += occupation >> j & 1;

		occupation &= ~(1 << (j - 1));
		perm[i] = j - 1;
	}
}
