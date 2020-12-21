#include <string>

static void test1_function() {}
void test1() { if (false) test1_function(); }

static void test2_function() {}
void static test2(bool d = false) { if (d) test2_function(); }
void call_test2() { test2(); }

enum Switcher { ON,OFF };
static void test3_function() {}
void static test3(Switcher s = OFF) {
    switch (s) {
        case ON:
        case OFF:
            break;
        default:
            test3_function();
            break;
    }
}
void call_test3(){ test3();}

class Test4 {
    void test4_function() {}
public:
    // https://youtrack.jetbrains.com/issue/CPP-23431
    void test4() { if (this == nullptr) test4_function(); }
};

class Base {
    virtual void test5_function() {};
};

class Test5: public Base {
    void test5_function() override {}
public:
    // https://youtrack.jetbrains.com/issue/CPP-23436
    void test5() {
        bool a = false;
        if (a) test5_function();
    }
};

namespace {
    bool flag = false;
    void test6_function() {}
    void test6() {
        if (flag) test6_function();
    }

    std::string test7_function() { return ""; }
    void test7() {
        if (flag) test6_function();
    }

    template<typename T>
    void test8_function() {}
    // https://youtrack.jetbrains.com/issue/CPP-23438
    template<typename T>
    void test8() {
        if (flag) test8_function<T>();
    }
}


class Test9 {
    static void test9_function() {}

public:
    void test9() {
        bool a = false;
        if (a) test9_function();
    }
};

void chekGlobalDFA() {
    ::test6();
    ::test7();
    ::test8<int>();
}