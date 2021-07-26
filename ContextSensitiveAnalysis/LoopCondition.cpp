// summary: should be 9 warnings + 1 pop

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-suspicious-semicolon"
#pragma ide diagnostic ignored "ConstantParameter"
// Local DFA
namespace loop_condition {
    // https://youtrack.jetbrains.com/issue/CPP-23459
    void test1() {
        for (int i = 0; i < 10;) {
            if (i > 5)
                break;
        }
    }

    void test2(int a) {
        while (a < 10) { // warn here
        }
    }

    void test3(int a) {
        do {

          } while (a < 10); // warn here
    }

    void test4() {
        for (int i = 0; i < 10; ) { // warn here

        }
    }

    void test5(int i = 0) {
        for (; i < 10; ) { // warn here

        }
    }
}


// Global DFA
namespace {
    // https://youtrack.jetbrains.com/issue/CPP-23459
    void test1() {
        for (int i = 0; i < 10;) { // warn here
            if (i > 5)
                ;//code
        }
    }

    void test2(int a) {
        while (a < 10) { // warn here
        }
    }

    void test3(int a) {
        do {

        } while (a < 10); // warn here
    }

    void test4() {
        for (int i = 0; i < 10; ) { // warn here

        }
    }

    void test5(int i = 0) {
        for (; i < 10; ) { // warn here

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