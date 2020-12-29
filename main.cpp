static float foo(int x, float b = 0.17) {
    if (x > 0)
        return b;
    return 0.17;
}

int main() {
    foo(1);
}