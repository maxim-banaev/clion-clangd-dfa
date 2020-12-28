// summary: should be 9 warnings
// Local DFA
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantParameter"
namespace loop_condition {
    // https://youtrack.jetbrains.com/issue/CPP-23459
    void test1() {
        for (int i = 0; i < 10;) {
            if (i > 5)
                break;
        }
    }

    void test2(int a) {
        while (a < 10) {
        }
    }

    void test3(int a) {
        do {

        } while (a < 10);
    }

    void test4() {
        for (int i = 0; i < 10; ) {

        }
    }

    void test5(int i = 0) {
        for (; i < 10; ) {

        }
    }
}


// Global DFA
namespace {
    // https://youtrack.jetbrains.com/issue/CPP-23459
    void test1() {
        for (int i = 0; i < 10;) {
            if (i > 5)
                break;
        }
    }

    void test2(int a) {
        while (a < 10) {
        }
    }

    void test3(int a) {
        do {

        } while (a < 10);
    }

    void test4() {
        for (int i = 0; i < 10; ) {

        }
    }

    void test5(int i = 0) {
        for (; i < 10; ) {

        }
    }
}

void checkGlobalDFA() {
    ::test1();
    ::test2(2);
    ::test3(3);
    ::test4();
    ::test5();
}

#pragma clang diagnostic pop