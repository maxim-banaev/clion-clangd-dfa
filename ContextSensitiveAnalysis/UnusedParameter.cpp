// Local DFA
namespace unused_parameter {
    void test1(int p) {}
}

// Global DFA
namespace {
    // https://youtrack.jetbrains.com/issue/CPP-23482
    void test1(int p) {}

    void test2(float p) {}
}


void checkGlobalDFA() {
    ::test1(1);
    ::test2(2.0);
}