#include <string.h>
#include "permcode.h"

/* binning with a bin size of 4 */
#define BINSIZE 4
#define BINCOUNT ((SQ_COUNT+BINSIZE-1)/BINSIZE)
const char *algname = "bin4";

extern void encode(unsigned char perm[PC_COUNT])
{
	size_t i, j, bin;
	unsigned char occupation[BINCOUNT * BINSIZE], bins[BINCOUNT];

	for (i = 0; i < BINCOUNT; i++) {
		bins[i] = BINSIZE * i;
		for (j = 0; j < BINSIZE; j++)
			occupation[BINSIZE * i + j] = j;
	}

	for (i = 0; i < PC_COUNT; i++) {
		bin = perm[i] / BINSIZE;

		for (j = perm[i] + 1; j < (bin + 1) * BINSIZE; j++)
			occupation[j]--;

		for (j = bin + 1; j < BINCOUNT; j++)
			bins[j]--;

		perm[i] = bins[bin] + occupation[perm[i]];
	}
}

extern void decode(unsigned char perm[PC_COUNT])
{
	size_t i, j, bin;
	unsigned char occupation[BINCOUNT * BINSIZE], bins[BINCOUNT + 1];

	for (i = 0; i < BINCOUNT; i++) {
		bins[i] = BINSIZE * i;
		for (j = 0; j < BINSIZE; j++)
			occupation[BINSIZE * i + j] = j;
	}

	bins[BINCOUNT] = BINSIZE * BINCOUNT;

	for (i = 0; i < PC_COUNT; i++) {
		for (bin = 0; bins[bin] <= perm[i]; bin++)
			;

		for (j = --bin * BINSIZE; occupation[j] < perm[i] - bins[bin]; j++)
			;

		perm[i] = j;

		for (j++; j < (bin + 1) * BINSIZE; j++)
			occupation[j]--;

		for (bin++; bin < BINCOUNT; bin++)
			bins[bin]--;
	}
}
