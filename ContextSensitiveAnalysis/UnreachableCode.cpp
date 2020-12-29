// summary: should be 43 warnings

#include <vector>
#include <iostream>

// Local DFA
#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
#pragma ide diagnostic ignored "ConstantParameter"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "UnusedLocalVariable"
#pragma ide diagnostic ignored "UnusedValue"
#pragma ide diagnostic ignored "ConstantConditionsOC"
#pragma ide diagnostic ignored "EndlessLoop"
namespace null_dereferences {
    void test() {
        return;
        int i_am_unreachable;
    }

    [[noreturn]] void test1() {
        while (true) {
        }

        int i_am_unreachable;
    }

    void test2() {
        foo:
        int a = 1;

        if (a == 1)
            goto foo;

        [[maybe_unused]] int i_am_unreachable;
    }

    void test3(int a = 1) {
        switch (a) {
            case 1:
                std::cout << "1";
                break;
            case 2:
                std::cout << "2";
                break;
                int i_am_unreachable;
            default:
                std::cout << "hz";
                break;
        }
    }

    void test4(bool flag) {
        std::string str = (flag || true) ? "reachable" : "i_am_unreachable";
    }

    void test5() {
        while (false) {
            int i_am_unreachable;
        }
    }

    void test6() {
        int x = 0;
        if (true || false)
            x++;
        else
            int i_am_unreachable;
    }

    void test7() {
        for (int i = 0; i < 100; ++i) {
            continue;
            int i_am_unreachable;
        }

        for (int i = 0; i < 100; ++i) {
            break;
            int i_am_unreachable;
        }

        for (int i = 0; i < 100; ++i) {
            return;
            int i_am_unreachable;
        }

        std::vector<int> range = {1, 2, 3};
        for (const auto &item : range) {
            continue;
            int i_am_unreachable;
        }

        for (const auto &item : range) {
            break;
            int i_am_unreachable;
        }

        for (const auto &item : range) {
            return;
            int i_am_unreachable;
        }
    }

    template<typename T>
    T test8() {
        T t;
        return t;
        T t1;
    }

    class never_happens : public std::exception {

    };

    void test9() {
        try {
            int a;
        } catch (never_happens &e) {
            int i_am_unreachable;
        }
    }

    void test10() {
        try {
            int a;
        } catch (std::bad_alloc &e) {
            int i_am_reachable; // shouldn't war here.
        } catch (...) {
            int i_am_unreachable;
        }
    }

    void test11() {
        try {
            int a = 1;
        } catch (...) {
            int i_am_unreachable;
        }
    }

    void test12() {
        try {
            int a = 1;
        } catch (...) {
            int i_am_unreachable;
        }
    }
} // namespace

// Global DFA
namespace {
    void test() {
        return;
        int i_am_unreachable;
    }

    [[noreturn]] void test1() {
        while (true) {
        }

        int i_am_unreachable;
    }

    void test2() {
        foo:
        int a = 1;

        if (a == 1)
            goto foo;

        int i_am_unreachable;
    }

    void test3(int a = 1) {
        switch (a) {
            case 1:
                std::cout << "1";
                break;
            case 2:
                std::cout << "2";
                break;
                int i_am_unreachable;
            default:
                std::cout << "hz";
                break;
        }
    }

    void test4(bool flag) {
        std::string str = (flag || true) ? "reachable" : "i_am_unreachable";
    }

    void test5() {
        while (false) {
            int i_am_unreachable;
        }
    }

    void test6() {
        int x = 0;
        if (true || false)
            x++;
        else
            int i_am_unreachable;
    }

    void test7() {
        for (int i = 0; i < 100; ++i) {
            continue;
            int i_am_unreachable;
        }

        for (int i = 0; i < 100; ++i) {
            break;
            int i_am_unreachable;
        }

        for (int i = 0; i < 100; ++i) {
            return;
            int i_am_unreachable;
        }

        std::vector<int> range = {1, 2, 3};
        for (const auto &item : range) {
            continue;
            int i_am_unreachable;
        }

        for (const auto &item : range) {
            break;
            int i_am_unreachable;
        }

        for (const auto &item : range) {
            return;
            int i_am_unreachable;
        }
    }

    template<typename T>
    T test8() {
        T t{};
        return t;
        T t1;
    }

    class never_happens : public std::exception {

    };

    void test9() {
        try {
            int a;
        } catch (never_happens &e) {
            int i_am_unreachable;
        }
    }

    void test10() {
        try {
            int a;
        } catch (std::bad_alloc &e) {
            int i_am_reachable; // shouldn't war here.
        } catch (...) {
            int i_am_unreachable;
        }
    }

    //https://youtrack.jetbrains.com/issue/CPP-22439
    void test11() {
        try {
            int a = 1;
        } catch (...) {
            int i_am_unreachable; // shouldn't war here.
        }
    }

} // namespace

void checkGlobalDFA() {
    ::test();
    ::test2();
    ::test3(1);
    ::test4(true);
    ::test5();
    ::test6();
    ::test7();
    ::test8<int>();
    ::test9();
    ::test10();
    ::test11();
    ::test1();
}
#pragma clang diagnostic pop