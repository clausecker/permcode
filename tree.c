#include <string.h>
#include <stddef.h>
#include "permcode.h"

/* difference trees */
const char *algname = "tree";

extern void encode(unsigned char perm[PC_COUNT])
{
	unsigned char tree[16] = {
		8,
		4, 4,
		2, 2, 2, 2,
		1, 1, 1, 1,  1, 1, 1, 1
	};

	size_t path, code, i, j, dir;

	for (i = 0; i < PC_COUNT; i++) {
		path = 16 | perm[i];
		code = 0;

		for (j = 0; j < 4; j++) {
			dir = path & 1;
			path >>= 1;

			if (dir)
				code += tree[path - 1];
			else
				tree[path - 1]--;
		}

		perm[i] = code;
	}
}

extern void decode(unsigned char perm[PC_COUNT])
{
	unsigned char tree[16] = {
		8,
		4, 4,
		2, 2, 2, 2,
		1, 1, 1, 1,  1, 1, 1, 1
	};

	size_t path, code, i, j;

	for (i = 0; i < PC_COUNT; i++) {
		path = 1;
		code = perm[i];

		for (j = 0; j < 4; j++) {
			if (code < tree[path - 1]) {
				tree[path - 1]--;
				path <<= 1;
			} else {
				code -= tree[path - 1];
				path = (path << 1) + 1;
			}
		}

		perm[i] = path & 15;
	}
}
