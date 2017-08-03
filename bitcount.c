#include <string.h>
#include "permcode.h"

/* count places to the left with bit fiddling */
const char *algname = "bitcount";

extern void encode(unsigned char perm[PC_COUNT])
{
	size_t i, j;
	unsigned count;
	unsigned occupation = (1 << SQ_COUNT) - 1, map;

	for (i = 0; i < PC_COUNT; i++) {
		count = occupation & (1 << perm[i]) - 1;
		count = count - (count >> 1 & 0x55555555);
		count = (count & 0x33333333) + (count >> 2 & 0x33333333);
		count = count + (count >> 4) & 0x0f0f0f0fu;
		occupation &= ~(1 << perm[i]);
		perm[i] = (count * 0x01010101u & 0xffffffffu) >> 24;
	}
}

extern void decode(unsigned char perm[PC_COUNT])
{
	size_t i;
	int count;
	unsigned occupation = (1 << SQ_COUNT) - 1;
	unsigned a, b, c, r, s, t;

	for (i = 0; i < PC_COUNT; i++) {
		a = occupation - (occupation >> 1 & 0x55555555);
		b = (a & 0x33333333) + (a >> 2 & 0x33333333);
		c = b + (b >> 4) & 0x0f0f0f0f;

		r = perm[i] + 1;
		s = 0;
		t = c + (c >> 8) & 0xff;

		if (r > t) {
			s += 16;
			r -= t;
		}

		t = c >> s & 0xf;

		if (r > t) {
			s += 8;
			r -= t;
		}

		t = b >> s & 0x7;

		if (r > t) {
			s += 4;
			r -= t;
		}

		t = a >> s & 0x3;

		if (r > t) {
			s += 2;
			r -= t;
		}

		t = occupation >> s & 0x1;

		if (r > t)
			s++;

		perm[i] = s;
		occupation &= ~(1 << s);
	}
}
