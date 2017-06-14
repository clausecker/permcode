#include <string.h>
#include <emmintrin.h>
#include <xmmintrin.h>
#include "permcode.h"

/* use a 64 bit vector of 4 bit numbers with SSE2 intrinsics */
const char *algname = "sse1";

extern void encode(unsigned char perm[PC_COUNT])
{
	size_t i, j;
	int count;
	__m128i occupation = _mm_set_epi32(0, 0, 0xfedcba98u, 0x76543210u);
	__m128i mask = _mm_set_epi32(0, 0, 0x11111111u, 0x11111110u), idx;

	for (i = 0; i < PC_COUNT; i++) {
		idx = _mm_cvtsi32_si128(4 * perm[i]);
		occupation = _mm_sub_epi8(occupation, _mm_sll_epi64(mask, idx));
		perm[i] = 15 & _mm_cvtsi128_si32(_mm_srl_epi64(occupation, idx));
	}
}

extern void decode(unsigned char perm[PC_COUNT])
{
	size_t i, j;
	int count;
	__m128 occupation = _mm_set_epi32(0, 0, 0xfedcba98u, 0x76543210u);
	__m128 mask, idx, idx_compl, mask0 = _mm_set1_epi8(0xff);

	for (i = 0; i < PC_COUNT; i++) {
		idx = _mm_cvtsi32_si128(4 * perm[i]);
		idx_compl = _mm_cvtsi32_si128(64 - 4 * perm[i]);
		mask = _mm_srl_epi64(mask0, idx_compl);
		perm[i] = 15 & _mm_cvtsi128_si32(_mm_srl_epi64(occupation, idx));
		occupation = _mm_or_si128(_mm_and_si128(mask, occupation),
		    _mm_andnot_si128(mask, _mm_srli_epi64(occupation, 4)));
	}

	_mm_empty();
}
