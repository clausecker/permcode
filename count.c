#include <string.h>
#include "permcode.h"

/* naive approach 1: count places to the left */
const char *algname = "count";

extern void encode(unsigned char perm[PC_COUNT])
{
	size_t i, j;
	int count;
	unsigned char occupation[SQ_COUNT];

	memset(occupation, 1, SQ_COUNT);

	for (i = 0; i < PC_COUNT; i++) {
		count = 0;
		for (j = 0; j < perm[i]; j++)
			count += occupation[j];
		occupation[perm[i]] = 0;
		perm[i] = count;
	}
}

extern void decode(unsigned char perm[PC_COUNT])
{
	size_t i, j;
	int count;
	unsigned char occupation[SQ_COUNT];

	memset(occupation, 1, SQ_COUNT);

	for (i = 0; i < PC_COUNT; i++) {
		count = 0;
		for (j = 0; count <= perm[i]; j++)
			count += occupation[j];

		occupation[j - 1] = 0;
		perm[i] = j - 1;
	}
}
