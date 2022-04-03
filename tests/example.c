int foo(int x);
int bar(int x, int y);

int qq(double x, int (*fp)(int, int, int)) {
    return bar(x, 2 * x) + foo(42) + fp(1, 2, 3);
}
