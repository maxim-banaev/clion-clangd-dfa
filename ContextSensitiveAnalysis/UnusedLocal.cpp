#include <string>
#include <vector>

// Local DFA
namespace unused_local {
    [[noreturn]] void test1() {
        int x = 0;
        x++;
    }

    void test2(int x) {}

    void test3() {
        int x = 2;
        x = x + 1;
    }

    class foo {
        int x;

    public:
        static void test4(int x) { int y; }
    };

    void test5(foo f) { foo f1{}; }

    void test6() { std::string s = "123"; }

    void test7(std::string s, std::vector<int> v) {
        std::string s1;
        std::vector<int> v1;
    }

    void test7_1(std::string s = "123") {
    }

    template<typename T>
    void test8(T t) {}

    void test9() {
        auto l = []() {
            int a;
        };
    }

    void test9_1() {
        auto l = []() {};
    }

    void test9_2() {
        auto l = [=]() {};
    }

    void test9_3() {
        auto l = [&]() {};
    }
} // namespace


// Global DFA
namespace {
    [[noreturn]] void test1() {
        int x = 0;
        x++;
    }

    void test2(int x) {}

    void test3() {
        int x = 2;
        x = x + 1;
    }

    class foo {
        int x;

    public:
        static void test4(int x) { int y; }
    };

    void test5(foo f) { foo f1{}; }

    void test6() { std::string s = "123"; }

    void test7(std::string s, std::vector<int> v) {
        std::string s1;
        std::vector<int> v1;
    }

    void test7_1(std::string s = "123") {
    }

    template<typename T>
    void test8(T t) {}

    void test9() {
        auto l = []() {
            int a;
        };
    }

    void test9_1() {
        auto l = []() {};
    }

    void test9_2() {
        auto l = [=]() {};
    }

    void test9_3() {
        auto l = [&]() {};
    }
} // namespace

void checkGlobalDFA() {
    ::test2(1);
    ::test3();
    foo::test4(1);
    ::test5({});
    ::test6();
    ::test7("_", {1});
    ::test7_1();
    ::test8(1);
    ::test9();
    ::test9_1();
    ::test9_2();
    ::test9_3();
}