// summary: 9 warnings
// Local DFA

#include <string>
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedStructInspection"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "ConstantParameter"
#pragma ide diagnostic ignored "performance-unnecessary-value-param"
namespace unused_parameter {
    void test1(int p) {}

    void test2(float p) {}

    void test3(const std::string p) {}

    // https://youtrack.jetbrains.com/issue/CPP-9788
    void test4(int& p) {}

    void test5(int* p) {}

    class X {
    public:
        void test10(int p) {}
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
}


void checkGlobalDFA() {
    ::test1(1);
    ::test2(2.0);
    ::test3("");
    int a{0};
    ::test4(a);
}
#pragma clang diagnostic pop