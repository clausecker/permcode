#include <stddef.h>
#include <x86intrin.h>
#include "permcode.h"

/* use BMI2 (i.e. pext and pdep) */
const char *algname = "bmi2";

extern void encode(unsigned char perm[PC_COUNT])
{
	unsigned occupation = -1, code;
	size_t i;

	for (i = 0; i < PC_COUNT; i++) {
		code = _pext_u32(1 << perm[i], occupation);
		occupation &= ~(1 << perm[i]);
		perm[i] = __builtin_ctz(code);
	}
}

extern void decode(unsigned char perm[PC_COUNT])
{
	unsigned occupation = -1, code;
	size_t i;

	for (i = 0; i < PC_COUNT; i++) {
		code = _pdep_u32(1 << perm[i], occupation);
		occupation &= ~code;
		perm[i] = __builtin_ctz(code);
	}
}
