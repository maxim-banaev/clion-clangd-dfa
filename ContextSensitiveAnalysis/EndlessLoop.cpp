namespace {
    void test1() {
        for (;;) {}
    }

    [[noreturn]] void test2() {
        for (;;) {} // should'n be there
    }

    void test3() {
        while (true) {}
    }

    void test4() {
        do {} while (true);

    }

    void test5() {
        foo:
        int foobla;
        int barbla;
        goto foo;
    }
}




