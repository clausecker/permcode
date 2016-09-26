#include <string.h>
#include <stddef.h>
#include "permcode.h"

/* difference trees with x86 asm */
const char *algname = "treeasm";

extern void encode(unsigned char perm[PC_COUNT])
{
	unsigned tree[32] = {
		16,
		8, 8,
		4, 4, 4, 4,
		2, 2, 2, 2,  2, 2, 2, 2,
		1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1
	};

	size_t i, j;
	unsigned path, code, zero, scratch;

	for (i = 0; i < PC_COUNT; i++) {
		path = 32 | perm[i];
		code = 0;

		for (j = 0; j < 5; j++) {
			zero = 0;
			asm(
				"shr %[path]"
				"\n\tmov (%[tree],%q[path],4),%[scratch]"
				"\n\tcmovc %[scratch],%[zero]"
				"\n\tcmc"
				"\n\tsbbl $0, %[scratch]"
				: [path]"+r"(path), [zero]"+r"(zero), [scratch]"=r"(scratch)
				: [tree]"r"(tree - 1)
				: "memory"
			);
			code += zero;
			tree[path - 1] = scratch;
		}

		perm[i] = code;
	}
}

extern void decode(unsigned char perm[PC_COUNT])
{
	unsigned tree[32] = {
		16,
		8, 8,
		4, 4, 4, 4,
		2, 2, 2, 2,  2, 2, 2, 2,
		1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1
	};

	size_t i, j;
	unsigned path, code, zero, here;

	for (i = 0; i < PC_COUNT; i++) {
		path = 1;
		code = perm[i];

		for (j = 0; j < 5; j++) {
			zero = 0;
			here = tree[path - 1];

			asm(
				"cmp %[here], %[code]"
				"\n\tcmovae %[here], %[zero]"
				"\n\tsbbl $0, (%[tree], %q[path], 4)"
				"\n\tcmp %[here], %[code]"
				"\n\tcmc"
				"\n\tadc %[path], %[path]"
				: [path]"+r"(path), [zero]"+r"(zero)
				: [code]"r"(code), [tree]"r"(tree - 1), [here]"r"(here)
				: "memory"
			);

			code -= zero;
		}

		perm[i] = path & 31;
	}
}
