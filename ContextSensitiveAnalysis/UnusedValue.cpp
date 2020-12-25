// Local DFA
#include <string>
#include <vector>

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
}

void checkGlobalDFA() {
    ::test1();
    ::test2();
    ::test3();
    ::test4();
    ::test5();
}
