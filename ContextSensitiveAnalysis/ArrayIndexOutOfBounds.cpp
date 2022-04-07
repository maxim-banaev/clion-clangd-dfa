#include <array>
#include <vector>
#include <iostream>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warray-bounds"

// local DFA
namespace array_index_out_of_bounds {
    void test1() {
        int *a = new int[10];
        a[11] = 11; // warn here
    }

#define N 11

    void test1_1() {
        int *a = new int[10];
        a[N] = 11; // warn here
    }

    void test2() {
        int *a = new int[1];
        for (int i = 0; i < 2; ++i) a[i] = i; // warn here
    }

    void test3() {
        auto *a = new int[2];
        for (int i = 0; i < 3; ++i) a[i] = i; // warn here
    }

    void test4() {
        int *a = new int[10];
        for (int i = 11; i >= 0; --i) a[i] = i; // warn here?
    }

    void test5() {
        int a[2][2] = {1, 2, 3, 4};
        [[maybe_unused]] int c = a[0][3];

    }

    void test5_1() {
        int **a = new int *[10];
        for (int i = 0; i < 10; ++i)
            a[i] = new int[10];

        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 11; ++j) {
                a[i][j] = i + j;
            }
        }
    }

    void test6() {
        struct foo {
            int a;

            foo() = default;

            [[maybe_unused]] foo(int a) : a(a) {} // NOLINT(google-explicit-constructor)
        };

        foo *f = new foo[3];
        f[6] = 1;
    }

    void test7() {
        int arr[] = {1, 2, 3, 4, 5};
        printf("arr[7] is %d\n", arr[7]);
    }

    void test8() {
        int arr[] = {1, 2, 3, 4, 5};
        printf("arr[7] is %d\n", arr[7]);
    }

    void test10() {
        std::array<int, 5> array = {1, 2, 3, 4, 5};
        for (int i = 0; i < 10; ++i) array[i] = i; // warn here?
    }

    void test11() {
        std::vector<int> vec = {3, 1, 4, 1, 5};
        try {
            vec.at(5) = 9; // warn here?
        }
        catch (...) {
            std::cout << "Out-of-bounds exception captured!\n";
        }
    }
}

// global DFA
namespace {
    void test1() {
        int *a = new int[10];
        for (int i = 0; i < 11; ++i) a[i] = i; // warn here
    }
}

void checkGlobalDFA() {
    ::test1();
}

#pragma clang diagnostic pop