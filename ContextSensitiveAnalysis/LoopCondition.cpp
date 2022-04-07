// summary: should be 10

#include <vector>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantConditionsOC"
#pragma ide diagnostic ignored "EndlessLoop"
#pragma ide diagnostic ignored "bugprone-suspicious-semicolon"
#pragma ide diagnostic ignored "ConstantParameter"
// Local DFA
namespace loop_condition {
    void test1() {
      for (int i = 0; i < 10;) { // warn here
            if (i > 5)
                ;
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
        for (auto i = 0; i < 10; ) { // warn here

        }
    }

    void test5(int i = 0) {
        for (; i < 10; ) { // warn here

        }
    }

    // https://youtrack.jetbrains.com/issue/CPP-25978
    void test6(const std::vector<int> & v) {
      for (auto wrapIter = v.begin(); wrapIter != v.end();) {

      }
    }
}


// Global DFA
namespace {
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

    // https://youtrack.jetbrains.com/issue/CPP-25978
    void test6(const std::vector<int> & v) {
      for (auto wrapIter = v.begin(); wrapIter != v.end();) {

      }
    }
}

void checkGlobalDFA() {
    ::test1();
    ::test2(2);
    ::test3(3);
    ::test4();
    ::test5();
    ::test6({6});
}

#pragma clang diagnostic pop