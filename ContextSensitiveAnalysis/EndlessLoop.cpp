// summary: 30 warnings

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantConditionsOC"
#pragma ide diagnostic ignored "ConstantParameter"
#pragma ide diagnostic ignored "ConstantFunctionResult"
#pragma ide diagnostic ignored "UnreachableCode"
#pragma ide diagnostic ignored "UnusedLocalVariable"
// Local DFA
namespace endless_loop {
    void test1() {
        for (;;) { // warn here
        }
    }

    void test1_1() {
        for (;;) // warn here
            int a;
    }

    void test1_2() {
        for (;;) { // warn here
            int a;
            int b;
        }
    }

    [[noreturn]] void test2() {
        for (;;) {
            int a;
        } // shouldn't be there
    }

    void test3() {
        while (true) { // warn here
        }
    }

    void test3_1() {
        while (true) // warn here
            int a;
    }

    void test3_2() {
        while (true) { // warn here
            int a;
            int b;
        }
    }

    void test4() {
        do { // warn here
        } while (true);
    }

    void test4_1() {
        do { // warn here
            int a;
        } while (true);
    }

    void test4_2() {
        do // warn here
            int a;
        while (true);
    }

    void test5() {
        foo:
        int a; // warn here
        goto foo;
    }

    void test5_1() {
        foo:
        goto foo; // warn here
    }

    void test5_2() {
        foo:
        int a; // warn here
        goto bar;
        int i_am_unused;
        bar:
        int b; // warn here
        goto foo;
    }

    template<typename T>
    void test6() {
        while (true) { // warn here
        }
    }
} // namespace


// Global DFA
namespace {
    void test1() {
        for (;;) { // warn here
        }
    }

    void test1_1() {
        for (;;) // warn here
            int a;
    }

    void test1_2() {
        for (;;) { // warn here
            int a;
            int b;
        }
    }

    [[noreturn]] void test2() {
        for (;;) {
            int a;
        } // shouldn't be there
    }

    void test3() {
        while (true) { // warn here
        }
    }

    void test3_1() {
        while (true) // warn here
            int a;
    }

    void test3_2() {
        while (true) { // warn here
            int a;
            int b;
        }
    }

    void test4() {
        do { // warn here
        } while (true);
    }

    void test4_1() {
        do { // warn here
            int a;
        } while (true);
    }

    void test4_2() {
        do // warn here
            int a;
        while (true);
    }

    void test5() {
        foo:
        int a; // warn here
        goto foo;
    }

    void test5_1() {
        foo:
        goto foo; // warn here
    }

    void test5_2() {
        foo:
        int a; // warn here
        goto bar;
        int i_am_unused;
        bar:
        int b;
        goto foo;
    }

    template<typename T>
    void test6() {
        while (true) { // warn here
        }
    }

    bool getTrue(bool a = true) {
        return a;
    }
    void test7() {
        while (getTrue()) { // warn here
        }
    }
} // namespace

void checkGlobalDFA() {
    ::test1();
    ::test1_1();
    ::test1_2();
    ::test3();
    ::test3_1();
    ::test3_2();
    ::test4();
    ::test4_1();
    ::test4_2();
    ::test5();
    ::test5_1();
    ::test5_2();
    ::test6<int>();
    ::test7();
    ::test2();
}
#pragma clang diagnostic pop