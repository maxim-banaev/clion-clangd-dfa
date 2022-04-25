#include <array>
#include <vector>
#include <iostream>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NullDereference"
#pragma ide diagnostic ignored "UnusedValue"
#pragma ide diagnostic ignored "ConstantParameter"
#pragma ide diagnostic ignored "ConstantConditionsOC"

// local DFA
namespace array_index_out_of_bounds {
    void test1() {
        int *a = new int[0];
        a[1] = 11; // warn here
    }

#define N 1

    void test1_1() {
        int *a = new int[0];
        a[N] = 11; // warn here
    }

    void test2() {
        int *a = new int[2];
        for (int i = 0; i < 3; ++i) a[i] = i; // warn here
    }

    void test3() {
        auto *a = new int[3];
        for (int i = 0; i < 4; ++i) a[i] = i; // warn here
    }

    // https://youtrack.jetbrains.com/issue/CPP-29036
    void test4() {
        int *a = new int[10];
        for (int i = 11; i >= 0; --i) a[i] = i; // warn here?
    }

    void test5() {
        int a[2][4] = {1, 2, 3, 4};
        [[maybe_unused]] int c = a[0][5]; // warn here

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

        [[maybe_unused]] foo *f = new foo[3];
        f[6] = 1;
    }

    void test7() {
        int arr[] = {1, 2, 3, 4, 5};
        printf("arr[7] is %d\n", arr[7]); // warn here
    }

    void test8(int x) {
        int buf[7];

        if (x > 7)
            buf[x] = 1; // warn here
    }

    void test9() {
        std::array<int, 9> array = {1, 2, 3, 4, 5};
        for (int i = 10; i < 11; ++i) array[i] = i; // warn here
    }

    // will not be fixed
    void test10() {
        std::vector<int> vec = {3, 1, 4, 1, 5};
        try {
            vec.at(5) = 9; // warn here?
        }
        catch (...) {
            std::cout << "Out-of-bounds exception captured!\n";
        }
    }

    [[maybe_unused]] void test11(int x[10]) {
        x[11] = 1; // shouldn't warn here. Strange
    }

    [[maybe_unused]] void test12() {
        int *ip = new int;
        ip[1] = 2; //warn here?
    }

    //https://youtrack.jetbrains.com/issue/CPP-29038/
    void test13() {
        int x[12], i = 13;
        x[i++] = 1; // should warn here
    }

    enum {
        SIZE = 13,
        VALUE
    };
    void test14() {
        bool flags[SIZE];
        flags[VALUE] = true; // warn here
    }

    class [[maybe_unused]] test15 {
        [[maybe_unused]] int x[14]{};
    public:
        [[maybe_unused]] explicit test15() {
            this->x[15] = 1; // warn here
        }
    };

    void test16() {
        int x[15];
        if (x[16] == 1) {} // warn here
    }

    void test17() {
        std::string s[16];
        s[17] = "test17"; // warn here?
    }

    [[maybe_unused]] void test18() {
        int x[17];
        [[maybe_unused]] int c = (x[18]); // warn here
    }

    namespace {
        int test19[18];
        [[maybe_unused]] int c = test19[19]; // should warn here
    }
}

// global DFA
namespace {
    void test1() {
        int *a = new int[1];
        a[1] = 11; // warn here
    }

    void test1_1() {
        int *a = new int[1];
        a[N] = 11; // warn here
    }

    void test2() {
        int *a = new int[2];
        for (int i = 0; i < 3; ++i) a[i] = i; // warn here
    }

    void test3() {
        auto *a = new int[3];
        for (int i = 0; i < 4; ++i) a[i] = i; // warn here
    }

    // https://youtrack.jetbrains.com/issue/CPP-29036
    void test4() {
        int *a = new int[10];
        for (int i = 11; i >= 0; --i) a[i] = i; // warn here?
    }

    void test5() {
        int a[2][2] = {1, 2, 3, 4};
        [[maybe_unused]] int c = a[0][5]; // warn here

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

        [[maybe_unused]] foo *f = new foo[3];
        f[6] = 1;
    }

    void test7() {
        int arr[] = {1, 2, 3, 4, 5};
        printf("arr[7] is %d\n", arr[7]); // warn here
    }

    void test8(int x = 8) {
        int buf[7];

        if (x > 7)
            buf[x] = 1;
    }

    void test9() {
        std::array<int, 9> array = {1, 2, 3, 4, 5};
        for (int i = 0; i < 10; ++i) array[i] = i; // warn here
    }

    void test10(int x[10] = nullptr) {
        x[11] = 1; // shouldn't warn here. Strange
    }

    void test11() {
        int *ip = new int;
        ip[1] = 2; //warn here?
    }
}

void checkGlobalDFA() {
    ::test1();
    ::test1_1();
    ::test2();
    ::test3();
    ::test4();
    ::test5();
    ::test5_1();
    ::test6();
    ::test7();
    ::test8();
    ::test9();
    ::test10();
    ::test11();

}

#pragma clang diagnostic pop