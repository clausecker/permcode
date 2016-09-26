#include <string.h>
#include "permcode.h"

/* naive approach 2: decrement places to the right */
const char *algname = "decrement";

extern void encode(unsigned char perm[PC_COUNT])
{
	size_t i, j;
	unsigned char occupation[SQ_COUNT];

	for (i = 0; i < SQ_COUNT; i++)
		occupation[i] = i;

	for (i = 0; i < PC_COUNT; i++) {
		for (j = perm[i] + 1; j < SQ_COUNT; j++)
			occupation[j]--;

		perm[i] = occupation[perm[i]];
	}
}

extern void decode(unsigned char perm[PC_COUNT])
{
	size_t i, j;
	unsigned char occupation[SQ_COUNT];

	for (i = 0; i < SQ_COUNT; i++)
		occupation[i] = i;

	for (i = 0; i < PC_COUNT; i++) {
		for (j = 0; occupation[j] != perm[i]; j++)
			;

		perm[i] = j;

		for (j++; j < SQ_COUNT; j++)
			occupation[j]--;
	}
}
