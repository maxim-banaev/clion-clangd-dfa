// summary: 26 warnings

#include <iostream>
#include <string>


#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
#pragma ide diagnostic ignored "ConstantFunctionResult"
// Local DFA
namespace constant_condition {
    void test() {
        int a = 1;
        if (a == 1) { // warn here
        }

        // check the suppressing
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantConditionsOC"
        if (a != 0) {
        }
#pragma clang diagnostic pop
    }

#define A(x) x == 1

    void test1() {
        int a = 1;
        if (A(a)) {
        }
    }

    void test2() {
        int a = 0;
        int b = 0;

        int *a_ptr = &a;
        *a_ptr = 1; // Modifies a, now a=1, b=0.

        if (a != b) { // shouldn't be there
        }
    }

    void test3() {
        int first = 0;
        int last = 0;

        std::cin >> first >> last;

        if (first == last) { // shouldn't be there
        }
    }

    template<typename T>
    void test4();

    template<>
    void test4<int>() {
        int t1 = 0;
        int t2 = 0;
        if (t1 == t2) { // warn here
        }
    }

    void test5() {
        int *i = nullptr;
        if (i == nullptr) {} // warn here

        std::string *s = nullptr;
        if (s == nullptr) {} // warn here
    }

    typedef int X;

    void test6() {
        X i = 1;
        if (i == 1) {} // warn here
    }

#define X 1
#define Y y

    void test7() {
        int x = 1;
        int y = 1;

        if (x == X) {} // warn here
        if (X == x) {}
        if (Y == 1) {}
        if (1 == Y) {} // warn here
        if (x == Y) {} // warn here
        if (Y == x) {}
        if (Y == X) {}
        if (X == Y) {}
    }

    void test8() {
        float f = 0.5;
        if (f == 0.5) {} // warn here
    }

} // namespace


// Global DFA
namespace {
    void test() {
        int a = 1;
        if (a == 1) { // warn here
        }

        // check the suppressing
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantConditionsOC"
        if (a != 0) {
        }
#pragma clang diagnostic pop
    }

#define A(x) x == 1

    void test1() {
        int a = 1;
        if (A(a)) {
        }
    }

    void test2() {
        int a = 0;
        int b = 0;

        int *a_ptr = &a;
        *a_ptr = 1; // Modifies a, now a=1, b=0.

        if (a != b) { // shouldn't be there
        }
    }

    void test3() {
        int first = 0;
        int last = 0;

        std::cin >> first >> last;

        if (first == last) { // shouldn't be there
        }
    }

    template<typename T>
    void test4();

    template<>
    void test4<int>() {
        int t1 = 0;
        int t2 = 0;
        if (t1 == t2) { // warn here
        }
    }

    void test5() {
        int *i = nullptr;
        if (i == nullptr) {} // warn here

        std::string *s = nullptr;
        if (s == nullptr) {} // warn here
    }

    typedef int X1;

    void test6() {
        X1 i = 1;
        if (i == 1) {} // warn here
    }

#define X 1
#define Y y

    void test7() {
        int x = 1;
        int y = 1;

        if (x == X) {} // warn here
        if (X == x) {}
        if (Y == 1) {}
        if (1 == Y) {} // warn here
        if (x == Y) {} // warn here
        if (Y == x) {}
        if (Y == X) {}
        if (X == Y) {}
    }


    int getZero() {
        int a = 0;
        return a;
    }

    int getOne() {
        int a = 1;
        return a;
    }

    void test8() {
        if (getZero() == 0) {} // warn here
        if (getZero()) {} // warn here
        if (!getZero()) {} // warn here
        if (getZero(
                // foo
                )) {} // warn here

        if (false) {
            asm("nop");
        } else if (getZero()) {} // warn here
    }

    void test9() {
        while (getZero()) {} // warn here
    }

    int test10() {
        return 0;
        if (getZero() == 0) {} // shouldn't warn here
    }

    void test11() {
        if (getZero() == 0) {} // warn here
        if (1 == getOne()) {} // warn here
        if (getZero() == getOne()) { }
    }

} // namespace


void checkGlobalDFA() {
    ::test();
    ::test1();
    ::test2();
    ::test3();
    ::test4<int>();
    ::test5();
    ::test6();
    ::test7();
    ::test8();
    ::test9();
    ::test10();
    ::test11();
}
#pragma clang diagnostic pop