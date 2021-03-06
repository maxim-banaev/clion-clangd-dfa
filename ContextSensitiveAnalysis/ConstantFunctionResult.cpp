// summary: 12 warnings
#include <string>
#include <unistd.h>

// Local DFA
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "UnusedValue"
#pragma ide diagnostic ignored "OCUnusedStructInspection"
#pragma ide diagnostic ignored "UnusedLocalVariable"
#pragma ide diagnostic ignored "misc-no-recursion"
#pragma ide diagnostic ignored "ConstantConditionsOC"
#pragma ide diagnostic ignored "ConstantParameter"
namespace constant_function_result {
    // https://youtrack.jetbrains.com/issue/CPP-23365
    bool test1() {
        return true;
    }

    // https://youtrack.jetbrains.com/issue/CPP-23365
    bool test1_2() {
        return (true);
    }

    int test2() {
        int a = 0;
        return a;
    }

    char test3() {
        auto a = 'c';
        return a;
    }

    float test4() {
        float a = 1.1;
        return a;
    }

    enum class Letter {
        A
    };

    Letter test5() {
        Letter l = Letter::A;
        return l;
    }


    // https://youtrack.jetbrains.com/issue/CPP-23490
    bool test11() {
        auto a = true;
        auto b = false;
        return a && b;
    }
}

// Global DFA
namespace {
    // https://youtrack.jetbrains.com/issue/CPP-23365
    bool test1() {
        return true;
    }

    bool test1_1(int x, bool b = true) {
        if (x > 0)
            return b;
        return true;
    }

    auto test1_2(int x, bool b = true) -> bool{
        if (x > 0)
            return b;
        return true;
    }

    // It seems that inspection is working only with int-convertible types
    std::string test2(int x, std::string s = "") {
        if (x % 2 == 0)
            return s;
        sleep(x);
        return "";
    }

    char test3(int x, char c = '3') {
        if (x % 2 == 0)
            return c;
        sleep(x);
        return '3';
    }

    auto test4(int x, int b = 0) -> decltype(1){
        if (x > 0)
            return b;
        return 0;
    }

    // https://youtrack.jetbrains.com/issue/CPP-23367
    template<int N>
    int test5(int x, int b = N) {
        if (x > 0)
            return b;
        return N;
    }

    // https://youtrack.jetbrains.com/issue/CPP-23449
    template<typename T>
    T test6(T x, T b = 0) {
        if (x > 0)
            return b;
        return 0;
    }

    enum class Letter {
        A,
        B [[maybe_unused]]
    };

    Letter test7(int x, Letter l = Letter::A) {
        if (x > 0)
            return l;
        return Letter::A;
    }

    // https://youtrack.jetbrains.com/issue/CPP-23378
    int test8(int x) {
        if (random() % 2 == 0)
            return test8(x);
        return x;
    }

    void* test9(int x, void* p = nullptr) {
        if (x > 0)
            return p;
        return nullptr;
    }

    // https://youtrack.jetbrains.com/issue/CPP-23379
    int test10(int x, int b = 0) {
        if (x > 0)
            return b;
        return 0;
    }

    // https://youtrack.jetbrains.com/issue/CPP-23490
    bool test11() {
        auto a = true;
        auto b = false;
        return a && b;
    }
}

// https://youtrack.jetbrains.com/issue/CPP-23365
static bool test15() {
    return true;
}


class X {
    static int number;

    static int test16(int offset) {
        return offset;
    }

    // https://youtrack.jetbrains.com/issue/CPP-23519
    static int test17(int offset) {
        if (offset == 0) {
            return number;
        } else {
            return 1;
        }
    }

public:
    void check_test16() { // NOLINT(readability-convert-member-functions-to-static)
        int tmp = test16(0);
    }

    void check_test17() { // NOLINT(readability-convert-member-functions-to-static)
        int tmp = test17(0);
    }
};

int X::number = 0;

// https://youtrack.jetbrains.com/issue/CPP-23481
static float test18(int x, float b = 0.17) {
    if (x > 0)
        return b;
    return 0.17;
}


void checkGlobalDFA() {
    ::test1();
    ::test1_1(1);
    ::test1_2(1);
    ::test2(2);
    ::test3(3);
    ::test4(4);
    ::test5<0>(5);
    ::test6<int>(6);
    ::test7(7);
    ::test8(8);
    ::test9(9);

    std::function<int(int, int)> f_test10 = ::test10;
    f_test10(10, 0);
    ::test11();

    ::test15();

    X x;
    x.check_test16();
    x.check_test17();

    ::test18(18);
}

#pragma clang diagnostic pop