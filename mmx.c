#include <string.h>
#include <mmintrin.h>
#include "permcode.h"

/* use a 64 bit vector of 4 bit numbers with mmx intrinsics */
const char *algname = "mmx";

extern void encode(unsigned char perm[PC_COUNT])
{
	size_t i, j;
	int count;
	__m64 occupation = _mm_set_pi32(0xfedcba98u, 0x76543210u);
	__m64 mask = _mm_set_pi32(0x11111111u, 0x11111110u), idx;

	for (i = 0; i < PC_COUNT; i++) {
		idx = _mm_cvtsi32_si64(4 * perm[i]);
		occupation = _mm_sub_pi8(occupation, _mm_sll_si64(mask, idx));
		perm[i] = 15 & _mm_cvtsi64_si32(_mm_srl_si64(occupation, idx));
	}

	_mm_empty();
}

extern void decode(unsigned char perm[PC_COUNT])
{
	size_t i, j;
	int count;
	__m64 occupation = _mm_set_pi32(0xfedcba98u, 0x76543210u);
	__m64 mask, idx, idx_compl, mask0 = _mm_set1_pi8(0xff);

	for (i = 0; i < PC_COUNT; i++) {
		idx = _mm_cvtsi32_si64(4 * perm[i]);
		idx_compl = _mm_cvtsi32_si64(64 - 4 * perm[i]);
		mask = _mm_srl_si64(mask0, idx_compl);
		perm[i] = 15 & _mm_cvtsi64_si32(_mm_srl_si64(occupation, idx));
		occupation = _mm_or_si64(_mm_and_si64(mask, occupation),
		    _mm_andnot_si64(mask, _mm_srli_si64(occupation, 4)));
	}

	_mm_empty();
}
