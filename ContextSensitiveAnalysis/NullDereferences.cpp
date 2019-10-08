#include <memory>
#include <string>


namespace {
    struct foo {
        char data[42];
    };

    size_t test1() {
        struct foo *t = nullptr;
        return sizeof(t->data);
    }

    void test2() {
        std::string *a = nullptr;
        std::string b = "a";
        while (a == nullptr || a->length()) {
            a = &b;
        }
    }

    void test3() {
        bool *f = nullptr;
        char *c = nullptr;
        if (*f && *c) {

        }
    }

    void test4() {

    }
}