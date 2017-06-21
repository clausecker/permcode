#include <string.h>
#include "permcode.h"

/* count places to the left with bits */
const char *algname = "bitcount";

extern void encode(unsigned char perm[PC_COUNT])
{
	size_t i, j;
	unsigned count;
	unsigned occupation = (1 << PC_COUNT) - 1, map;

	for (i = 0; i < PC_COUNT; i++) {
		count = occupation & (1 << perm[i]) - 1;
		count = count - (count >> 1 & 0x55555555);
		count = (count & 0x33333333) + (count >> 2 & 0x33333333);
		count = count * 0x11110000 >> 28;
		occupation &= ~(1 << perm[i]);
		perm[i] = count;
	}
}

extern void decode(unsigned char perm[PC_COUNT])
{
	size_t i, j;
	int count;
	unsigned occupation = (1 << PC_COUNT) - 1;

	for (i = 0; i < PC_COUNT; i++) {
		count = 0;
		for (j = 0; count <= perm[i]; j++)
			count += occupation >> j & 1;

		occupation &= ~(1 << (j - 1));
		perm[i] = j - 1;
	}
}
