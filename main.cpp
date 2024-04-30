[[maybe_unused]] static void test2() {
    int *a = new int[2];
    for (int i = 0; i < 3; ++i)
        a[i] = i; // warn here
}

int main() {

}