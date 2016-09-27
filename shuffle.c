#include <assert.h>
#include <string.h>
#include "permcode.h"

/* Fisher-Yates shuffle, note that this generates a different encoding! */
const char *algname = "shuffle";

/*
 * This function reconstructs the parameters that went into a
 * Fisher-Yates shuffle by tracking where each item currently is in an
 * inverse permutation array.
 */
extern void encode(unsigned char perm[PC_COUNT])
{
	size_t i;
	unsigned char state[SQ_COUNT] = {
	     0,  1,  2,  3,  4,
	     5,  6,  7,  8,  9,
	    10, 11, 12, 13, 14,
	    15, 16, 17, 18, 19,
	    20, 21, 22, 23, 24
	}, inverse[SQ_COUNT] = {
	     0,  1,  2,  3,  4,
	     5,  6,  7,  8,  9,
	    10, 11, 12, 13, 14,
	    15, 16, 17, 18, 19,
	    20, 21, 22, 23, 24
	}, tmp, j;

	for (i = 0; i < PC_COUNT; i++) {
		/*
		 * this cryptic looking code is an optimized version of
		 * this pseudocode:
		 *
		 *     j = inverse[perm[i]]
		 *     swap entries state[i] and state[j] in inverse
		 *     swap entries i and j in state
		 *     perm[i] = j - i
		 *
		 * the optimization is using inverse[state[k]] == k and
		 * state[inverse[k]] == k for all 0 <= k < SQ_COUNT.
		 */
		j = inverse[perm[i]];
		inverse[perm[i]] = i;
		inverse[state[i]] = j;

		tmp = state[i];
		state[i] = perm[i];
		state[j] = tmp;

		perm[i] = j - i;
	}
}

extern void decode(unsigned char perm[PC_COUNT])
{
	size_t i;
	unsigned char state[SQ_COUNT] = {
	     0,  1,  2,  3,  4,
	     5,  6,  7,  8,  9,
	    10, 11, 12, 13, 14,
	    15, 16, 17, 18, 19,
	    20, 21, 22, 23, 24
	}, tmp;

	for (i = 0; i < PC_COUNT; i++) {
		tmp = state[i + perm[i]];
		state[i + perm[i]] = state[i];
		state[i] = tmp;
	}

	memcpy(perm, state, PC_COUNT);
}
