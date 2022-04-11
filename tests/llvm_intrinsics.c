#include <stdlib.h>
#include <string.h>

int CheckAssumeLikeIntrinsics(int a, int i) {
	int arr[4] = {a, a, a, a};

	return arr[i];
}

int main(void) {
	int* arr = (int*)calloc(5, sizeof(int));

	memset(arr, 0, 5 * sizeof(int));

	return 0;
}
