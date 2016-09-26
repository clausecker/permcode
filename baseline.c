#include <string.h>
#include "permcode.h"

/* baseline: do nothing */
const char *algname = "baseline";

extern void encode(unsigned char perm[PC_COUNT])
{
	size_t i;
	volatile unsigned char c;

	for (i = 0; i < PC_COUNT; i++)
		c = perm[i];
}
extern void decode(unsigned char perm[PC_COUNT])
{
	size_t i;
	volatile unsigned char c;

	for (i = 0; i < PC_COUNT; i++)
		c = perm[i];
}
