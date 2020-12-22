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
        if (flag) test7_function();
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
    void test9() { if (flag) test9_function();}
};

static void test10_function() {}
#define _FUNC_NAME test10_function
void test10() { if (flag) _FUNC_NAME(); }

static void test11_function();
static void test11_function() {}
void test11() { if (flag) test11_function();}

static void test12_function() {}
void do_nothing() {}
void test12() { flag ? test12_function() : do_nothing();}

static void test13_function() {}
// https://youtrack.jetbrains.com/issue/CPP-23440
void test13() {
    try {

    } catch (...) {
        test13_function();
    }
}

static void test14_function() {}
// https://youtrack.jetbrains.com/issue/CPP-23441
void test14() { return; test14_function();}

static void test15_function() {}
// https://youtrack.jetbrains.com/issue/CPP-23442
void test15() { while (true) {} test15_function();}

static void test16_function() {}
// https://youtrack.jetbrains.com/issue/CPP-23443
void test16() {
    goto test16_label;
    test16_function();
    test16_label:
    return;
}

static bool test17_function() { return true;}
void test17() {
    if ( !flag || test17_function()) { do_nothing(); }
}

static bool test18_function() { return true;}
void test18() {
    if ( !flag) { do_nothing();
    } else if (test18_function()) { }
}

static bool test19_function() { return true;}
void test19() {
    if ( flag && test19_function()) { do_nothing(); }
}

static bool test20_function() { return true;}
void test20(int a) {
    for (int i = 0; true || test20_function(); i++) {

    }
}

void chekGlobalDFA() {
    ::test6();
    ::test7();
    ::test8<int>();
}