// summary: 29 warnings

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
#pragma ide diagnostic ignored "UnusedLocalVariable"
// Local DFA
namespace endless_loop {
    void test1() {
        for (;;) {
        }
    }

    void test1_1() {
        for (;;)
            int a;
    }

    void test1_2() {
        for (;;) {
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
        while (true) {
        }
    }

    void test3_1() {
        while (true)
            int a;
    }

    void test3_2() {
        while (true) {
            int a;
            int b;
        }
    }

    void test4() {
        do {
        } while (true);
    }

    void test4_1() {
        do {
            int a;
        } while (true);
    }

    void test4_2() {
        do
            int a;
        while (true);
    }

    void test5() {
        foo:
        int a;
        goto foo;
    }

    void test5_1() {
        foo:
        goto foo;
    }

    void test5_2() {
        foo:
        int a;
        goto bar;
        int i_am_unused;
        bar:
        int b;
        goto foo;
    }

    template<typename T>
    void test6() {
        while (true) {
        }
    }
} // namespace


// Global DFA
namespace {
    void test1() {
        for (;;) {
        }
    }

    void test1_1() {
        for (;;)
            int a;
    }

    void test1_2() {
        for (;;) {
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
        while (true) {
        }
    }

    void test3_1() {
        while (true)
            int a;
    }

    void test3_2() {
        while (true) {
            int a;
            int b;
        }
    }

    void test4() {
        do {
        } while (true);
    }

    void test4_1() {
        do {
            int a;
        } while (true);
    }

    void test4_2() {
        do
            int a;
        while (true);
    }

    void test5() {
        foo:
        int a;
        goto foo;
    }

    void test5_1() {
        foo:
        goto foo;
    }

    void test5_2() {
        foo:
        int a;
        goto bar;
        int i_am_unused;
        bar:
        int b;
        goto foo;
    }

    template<typename T>
    void test6() {
        while (true) {
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
    ::test2();
}
#pragma clang diagnostic pop