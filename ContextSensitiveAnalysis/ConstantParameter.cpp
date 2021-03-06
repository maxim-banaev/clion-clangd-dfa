// summary: 24 warnings
// Constant parameter is working only with int-convertible types
// It's not working with other types even int() operator is defined
// https://youtrack.jetbrains.com/issue/CPP-23268


#include <climits>
#include <string>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
#pragma ide diagnostic ignored "ConstantFunctionResult"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "UnusedLocalVariable"
void static test1(int a) {

}

void static test2(const int &a) { // look like is not working also

}

void static test3(const std::string &s) {

}

void static test4(const int p) {}

void static test5(bool flag) {}

template<typename T>
void static test6(T t) {}

enum Color {
    Blue = 0
};
enum class Letter {
    A = 0
};

void static test7(Color c, Letter l) {}

void static test8(float a) {}

typedef int MyInt;
void static test9(MyInt a) {}

void static test10(float f) {}
void static test10_1(float f) {}
void static test10_2(double d) {}

namespace {
    void test11(int a) {}

    void test11_1(int a = 0) {}

    void test11_2(int a, int b) {}

    void test11_3(char c, int a) {}


    void test12() {}

    template<typename T>
    void test15(T t) {}

    template<typename T, typename U>
    void test16(T t, U u = '.'){}

    void test17(const int numbers...) {}
}


class X {
    [[maybe_unused]] static int zero;
    bool flag;

    void XTest1(unsigned p) {}

    static unsigned XTest2(unsigned p) {
        return p;
    }

public:
    void chechDFA() {
        XTest1(1);
        auto ret = flag ? XTest2(1) : 0;
    }
};

struct [[maybe_unused]] point {
    int x;
    int y;
};

void checkGlobalDFA() {
    test1(1);
    test2(2);
    test3("3");
    test4(4);
    test5(true);
    test6(1);
    test7(Blue, Letter::A);
    test8(0.5);
    test9(9);
    test10(10.5);
    //test10_1(4e2);
    test10_1(0x10.1p0);
    test10_2(123.456e-67);

    test11(INT_MAX);
    test11_1(0);
    test11_2(0, 1);
    test11_3('_', 1);

    test15<int>(0);
    test16<int, char>(1 );
    test17(1, 2);
}
#pragma clang diagnostic pop