#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int CheckAssumeLikeIntrinsics(int a, int i) {
	int arr[4] = {a, a, a, a};

	printf("%d, %d, %d, %d", 1, 2, 3, 4);

	return arr[i];
}

void CheckMemset(void) {
	int* arr1 = (int*)calloc(5, sizeof(int));

	memset(arr1, 0, 5 * sizeof(int));
}

void CheckMemcpy(void) {
	int* arr1 = (int*)calloc(5, sizeof(int));
	int* arr2 = (int*)calloc(5, sizeof(int));

	memcpy(arr2, arr1, 5);
}

void CheckMemmove(void) {
	int* arr1 = (int*)calloc(5, sizeof(int));
	int* arr2 = (int*)calloc(5, sizeof(int));
	
	memmove(arr2, arr1, 5);
}

int main(void) {
	return 0;
}
