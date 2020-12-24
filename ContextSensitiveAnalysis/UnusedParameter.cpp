// Local DFA
namespace unused_parameter {
    void test1(int p) {}
}

// Global DFA
namespace {
    void test1(int p) {}
}


void checkGlobalDFA() {
    ::test1(1);
}