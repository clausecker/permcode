#include <string.h>
#include "permcode.h"

/* count places to the left with popcount, decode with ctz */
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
	unsigned occupation = (1 << SQ_COUNT) - 1, tail;

	for (i = 0; i < PC_COUNT; i++) {
		tail = occupation;
		for (j = 0; j < perm[i]; j++)
			tail &= tail - 1;

		perm[i] = __builtin_ctz(tail);
		occupation &= tail - 1;
	}
}
