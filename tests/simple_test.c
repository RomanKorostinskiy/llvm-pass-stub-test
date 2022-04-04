#include <emmintrin.h>
#include <stdlib.h>
#include <stdio.h>
#include <immintrin.h>

int foo1(int a) {
	return 2;
}

int foo2(int a) {
	return foo1(1);
}

int foo3(int a) {
	return 1;
}

int foo4(int a) {
	return foo1(1);
}

int main(int argc, char* argv[]) {
	// __m128i m = _mm_set_ps (3, 2, 1, 0);
	// int* data = (int*)calloc(4, sizeof(int));
	// _mm_store_epi32 (data, m);

	// for (int i = 0; i < 4; i++) {
	// 	printf("%d\n", data[i]);
	// }

	return 	foo1(1) + foo2(1);
}
