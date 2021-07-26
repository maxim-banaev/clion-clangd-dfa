// summary: should be 8 warnings + 1 pop

#include <memory>
#include <string>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Winvalid-noreturn"
// local DFA
namespace null_dereference {
    struct foo {
        char data[42];
    };

    [[noreturn]] size_t test1() {
        struct foo *t = nullptr;
        t->data; // warn here
        sizeof(t->data); // shouldn't warn here
    }

    void test2(std::string *a, std::string b) {

        while (a != nullptr || a->length()) { // warn here
            a = &b;
        }

        std::string *a1 = nullptr;
        while (a1 == nullptr || a1->length()) { // shouldn't warn here
            a1 = &b;
        }
    }

    void test3() {
        bool *f = nullptr;
        char *c = nullptr;
        if (*f && *c) { // warn here
        }
    }

    void test4() {}
} // namespace

// global DFA
namespace {
    struct foo {
        char data[42];
    };

    [[noreturn]] size_t test1() {
        struct foo *t = nullptr;
        t->data; // warn here
        sizeof(t->data); // shouldn't warn here
    }

    void test2() {
        std::string *a = nullptr;
        std::string b = "a";

        while (a != nullptr || a->length()) { // warn here
            a = &b;
        }

        std::string *a1 = nullptr;
        while (a1 == nullptr || a1->length()) { // shouldn't warn here
            a1 = &b;
        }
    }

    void test3() {
        bool *f = nullptr;
        char *c = nullptr;
        if (*f && *c) { // warn here
        }
    }

    void test4() {}
} // namespace

void checkGlobalDFA() {
    ::test2();
    ::test3();
    ::test4();
    ::test1();
}
#pragma clang diagnostic pop