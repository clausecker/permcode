#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "permcode.h"

#define SAMPLES 10000000

int main()
{
	size_t i, j;
	clock_t begin, split, end;
	static unsigned char perms[SAMPLES][PC_COUNT];

	/* no srand() call to have reproduceable results */
	for (i = 0; i < SAMPLES; i++)
		for (j = 0; j < PC_COUNT; j++)
			perms[i][j] = rand() % (SQ_COUNT - j);

	
	begin = clock();

	for (i = 0; i < SAMPLES; i++)
		decode(perms[i]);

	split = clock();

	for (i = 0; i < SAMPLES; i++)
		encode(perms[i]);

	end = clock();

	printf("%-10s %7.4fs %7.4fs %7.4fs %8.4fns %8.4fns %8.4fns\n",
	    algname,
	    (split - begin)/(double)CLOCKS_PER_SEC, /* decode */
	    (end - split)/(double)CLOCKS_PER_SEC,   /* encode */
	    (end - begin)/(double)CLOCKS_PER_SEC,   /* total */
	    (split - begin)/(double)CLOCKS_PER_SEC/SAMPLES*1000000000, /* decode */
	    (end - split)/(double)CLOCKS_PER_SEC/SAMPLES*1000000000,   /* encode */
	    (end - begin)/(double)CLOCKS_PER_SEC/SAMPLES*1000000000);  /* total */

	return (0);
}
