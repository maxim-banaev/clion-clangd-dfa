// summary: 15 warnings
#include <string>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedStructInspection"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "ConstantParameter"
#pragma ide diagnostic ignored "performance-unnecessary-value-param"
// Local DFA
namespace unused_parameter {
    void test1(int p) {}

    void test2(float p) {}

    void test3(const std::string p) {}

    // https://youtrack.jetbrains.com/issue/CPP-9788
    void test4(int& p) {}

    void test5(int* p) {}

    void test6(std::function<int(void)> f) {}

    template<typename T>
    void test7(T t) {}

    void test8(const int numbers...) {}

    enum class Letter {
        A
    };
    void test9(Letter l) {}

    // https://youtrack.jetbrains.com/issue/CPP-23537
    void test10() {
        auto l = [](int p) {};

        l(1);
    }

    class X {
    public:
        void test15(int p) {}

        void test11(int p) const {}

        static void test12(int p) {}
    };
}

// Global DFA
namespace {
    // https://youtrack.jetbrains.com/issue/CPP-23482
    void test1(int p) {}

    void test2(float p) {}

    void test3(const std::string p) {}

    // https://youtrack.jetbrains.com/issue/CPP-9788
    void test4(int& p) {}

    // https://youtrack.jetbrains.com/issue/CPP-23537
    void test10() {
        auto l = [](int p) {};

        l(1);
    }
}


void checkGlobalDFA() {
    ::test1(1);
    ::test2(2.0);
    ::test3("");
    int a{0};
    ::test4(a);
    ::test10();
}
#pragma clang diagnostic pop