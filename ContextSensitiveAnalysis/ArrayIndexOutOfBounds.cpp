// summary: 25 warnings

#include <array>
#include <vector>
#include <iostream>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantParameter"
#pragma clang diagnostic ignored "-Warray-bounds"
#pragma clang diagnostic ignored "-Wunused-value"

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

    void test1_2() {
        int buf[100];
        int *p = buf;
        p[101] = 1; // warn here
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

    // https://youtrack.jetbrains.com/issue/CPP-28848
    void test5() {
        int a[2][2] = {1, 2, 3, 4};
        [[maybe_unused]] int c = a[0][3];

    }

    // https://youtrack.jetbrains.com/issue/CPP-28848
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
        f[6] = 1; // warn here
    }

    void test7() {
        int arr[] = {1, 2, 3, 4, 5};
        printf("arr[7] is %d\n", arr[7]); // warn here
    }

    void test8() {
        int buf[100];
        buf[-1] = 1; // warn here
    }

    // https://youtrack.jetbrains.com/issue/CPP-28847
    void test9() {
        const char *mystr = "mary had a little lamb";
        mystr[-1]; // warn here
        mystr[1000]; // warn here
    }

    void test10(int x) {
        int buf[100];
        if (x < 0)
            buf[x] = 1; // warn here
        else
            buf[x] = 0; // shouldn't warn here

        if (x > 99)
            buf[x] = 1; // warn here?
    }

    [[maybe_unused]] void test11(int x[10]) {
        x[11] = 1; // warn here?
    }

    // test12 for global mode

    void test13() {
        int x[12];
        auto l =[&]() {
            x[13] = 1; // warn here ?
        };
        l();

        auto l1 = [=]() {
            [[maybe_unused]] int c = x[13];// warn here ?
        };
        l1();
    }

    void test14_call([[maybe_unused]] int x){}
    void test14() {
        int x[13];
        test14_call(x[14]); //warn here
    }

    // https://youtrack.jetbrains.com/issue/CPP-28845
    void test15() {
        std::array<int, 5> array = {1, 2, 3, 4, 5};
        for (int i = 0; i < 10; ++i) array[i] = i; // warn here
    }

    // https://youtrack.jetbrains.com/issue/CPP-28845
    void test16() {
        std::vector<int> vec = {3, 1, 4, 1, 5};
        try {
            vec.at(5) = 9; // warn here
        }
        catch (...) {
            std::cout << "Out-of-bounds exception captured!\n";
        }
    }

    constexpr int get17(){
        return 17;
    }
    void test17() {
        int x[16];
        x[get17()]; // warn here
    }
}

// global DFA
namespace {
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

    // https://youtrack.jetbrains.com/issue/CPP-28848
    void test5() {
        int a[2][2] = {1, 2, 3, 4};
        [[maybe_unused]] int c = a[0][3];

    }
    // https://youtrack.jetbrains.com/issue/CPP-28848
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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantParameter"
#pragma ide diagnostic ignored "UnusedValue"

            [[maybe_unused]] foo(int a) : a(a) {} // NOLINT(google-explicit-constructor)
#pragma clang diagnostic pop
        };

        foo *f = new foo[3];
        f[6] = 1; // warn here
    }

    void test7() {
        int arr[] = {1, 2, 3, 4, 5};
        printf("arr[7] is %d\n", arr[7]); // warn here
    }

    void test8() {
        int buf[100];
        buf[-1] = 1; // warn here
    }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-value"
    // https://youtrack.jetbrains.com/issue/CPP-28847
    void test9() {
        const char *mystr = "mary had a little lamb";
        mystr[-1]; // warn here?
        mystr[1000]; // warn here?
    }
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantConditionsOC"
#pragma ide diagnostic ignored "UnreachableCode"
    void test10(int x) {
        int buf[100];
        if (x < 0)
            buf[x] = 1;
        else
            buf[x] = 0; // warn here

        if (x > 99)
            buf[x] = 1; // warn here
    }
#pragma clang diagnostic pop

    void test11(int x[10]) {
        x[11] = 1; // warn here
    }

    void test12(const int x) {
        int n[10];
        n[x] = 1; // warn here
    }

    void test12_1(const int x = 12) {
        int n[10];
        n[x] = 1; // warn here
    }

    void test13() {
        int x[12];
        auto l =[&]() {
            x[13] = 1; // warn here ?
        };
        l();

        auto l1 = [=]() {
            [[maybe_unused]] int c = x[13];// warn here ?
        };
        l1();
    }

    void test14_call([[maybe_unused]] int x){}
    void test14() {
        int x[13];
        test14_call(x[14]); //warn here
    }

    // https://youtrack.jetbrains.com/issue/CPP-28845
    void test15() {
        std::array<int, 5> array = {1, 2, 3, 4, 5};
        for (int i = 0; i < 10; ++i) array[i] = i; // warn here
    }

    // https://youtrack.jetbrains.com/issue/CPP-28845
    void test16() {
        std::vector<int> vec = {3, 1, 4, 1, 5};
        try {
            vec.at(5) = 9; // warn here
        }
        catch (...) {
            std::cout << "Out-of-bounds exception captured!\n";
        }
    }

    constexpr int get17(){
        return 17;
    }
    void test17() {
        int x[16];
        x[get17()]; // warn here
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
    ::test10(100);
    int x11[10] = {1,2,3,4,5,6,7,8,9,0};
    ::test11(x11);
    ::test12(12);
    ::test12_1();
    ::test13();
    ::test14();
    ::test15();
    ::test16();
    ::test17();
}

#pragma clang diagnostic pop