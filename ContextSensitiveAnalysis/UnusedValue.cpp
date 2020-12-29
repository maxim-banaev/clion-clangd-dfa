// summary: should be 28 warnings

#include <string>
#include <vector>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedLocalVariable"
#pragma ide diagnostic ignored "ConstantConditionsOC"
// Local DFA
namespace unused_value {
    int test1() {
        int a = 0; // warn
        int a1{0}; // warn
        a = 1;
        a1 = 1;
        return a + a1;
    }

    double test2() {
        double a = 0.1; // warn
        double a1{0.2}; // warn
        a = 1;
        a1 = 1;
        return a + a1;
    }

    bool test3() {
        auto a = false; // warn
        auto b{false}; // warn
        a = true;
        b = true;
        return a && b;
    }

    // https://youtrack.jetbrains.com/issue/CPP-23491
    std::string test4() {
        std::string a = "a"; // warn
        std::string b{"b"}; // should be warn here
        a = "_a";
        b = "_b";
        return a + b;
    }

    std::vector<int> test5() {
        std::vector<int> v = {1, 2, 3};
        return {1, 2, 3};
    }

    template<typename T>
    T test6() {
        T t = 0;
        t = 1;
        return t;
    }

    void test7() {
        auto a = 1.3F; // warn
        auto b = 1.3e19; // warn
    }

    void test8() {
        int* a = nullptr; // warn
        void *b = nullptr; // warn
    }

    void test9() {
        int a[] = {1,233};
    }

    void test10() {
        char p = '\0';
    }
}

// Global DFA
namespace {
    int test1() {
        int a = 0; // warn
        int a1{0}; // warn
        a = 1;
        a1 = 1;
        return a + a1;
    }

    double test2() {
        double a = 0.1; // warn
        double a1{0.2}; // warn
        a = 1;
        a1 = 1;
        return a + a1;
    }

    bool test3() {
        auto a = false; // warn
        auto b{false}; // warn
        a = true;
        b = true;
        return a && b;
    }

    // https://youtrack.jetbrains.com/issue/CPP-23491
    std::string test4() {
        std::string a = "a"; // warn
        std::string b{"b"}; // should be warn here
        a = "_a";
        b = "_b";
        return a + b;
    }

    std::vector<int> test5() {
        std::vector<int> v = {1, 2, 3};
        return {1, 2, 3};
    }

    template<typename T>
    T test6() {
        T t = 0;
        t = 1;
        return t;
    }

    void test7() {
        auto a = 1.3F; // warn
        auto b = 1.3e19; // warn
    }

    void test8() {
        int* a = nullptr; // warn
        void *b = nullptr; // warn
    }

    void test9() {
        int a[] = {1,233}; // warn
    }
}

void checkGlobalDFA() {
    ::test1();
    ::test2();
    ::test3();
    ::test4();
    ::test5();
    ::test6<int>();
    ::test7();
    ::test8();
    ::test9();
}

#pragma clang diagnostic pop