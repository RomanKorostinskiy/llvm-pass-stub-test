#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int foo1(int a) {
	return 2;
} /* foo1() */

int foo2(int a) {
	return 3;
} /* foo2() */

int foo3(int a) {
	return 1;
} /* foo3() */

int foo4(int a) {
	return 1;
} /* foo4() */

int main(int argc, char* argv[]) {
	// int (*bar)(int);

	foo1(1);
	foo2(1);

	// bar = foo3;
	// bar(1);

	return 0;
} /* main() */
