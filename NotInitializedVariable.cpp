#include <string>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
#pragma ide diagnostic ignored "UnusedLocalVariable"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma clang diagnostic ignored "-Winvalid-noreturn"
namespace not_initialized_variable {
    void test() {
        int a;
        if (a > 1) { // warn here
        }
    }

    struct X {
        int myFoo;
    };

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"

    [[noreturn]] int test1() {
        X x;
        return x.myFoo; // no 'not unitialized warning'
    }

#pragma clang diagnostic pop

    struct bla {
        double foo = 0;
    };

    bla test2() {
        bla out;
        return out;
    }

    void test3() {
        int a, b, c;
        for (a = 0; a < 1; a++) {
            c = a + 1;
        }
        b = c;
    }

    void test4() {
        int a;
        a++; // warn here
    }

    void test5() {
        int a, b;
        a = b; // warn here
    }

    void test6() {
        std::string s1, s2;
        s2 = s1;
    }

    template<typename T>
    T test7() {
        T t1, t2;
        t1 = t2;
        return t1;
    }


} // namespace
#pragma clang diagnostic pop