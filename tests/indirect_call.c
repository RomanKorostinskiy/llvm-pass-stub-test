#include <math.h>

int foo(int x) {
    return 1;
}
int bar(int x, int y) {
    return 2;
}

int qq(double x, int (*fp)(int, int, int)) {
    return bar(x, 2 * x) + foo(42) + fp(1, 2, 3);
}

int main() {
    return 0;
}
