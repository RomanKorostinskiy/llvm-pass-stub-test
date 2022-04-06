#include <stdlib.h>
#include <stdio.h>
#include <immintrin.h>

int main() {

	int arr1[4] = {0};
	int arr2[4] = {0};
	for (int i = 0; i < 4; i++) {
		scanf("%d", arr1 + i);
		scanf("%d", arr2 + i);
	}

	__m128i a = _mm_set_ps (arr1[0], arr1[1], arr1[2], arr1[3]);
	__m128i b = _mm_set_ps (arr2[0], arr2[1], arr2[2], arr2[3]);

	__m128i cmp = _mm_cmpeq_epi32 (a, b);

	int mask = _mm_movemask_epi8 (cmp);

	return mask;
}
