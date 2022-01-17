#include <cassert>

static void f(int a ) {
    assert(a == 1);
}

int main() {
    f(1);
}