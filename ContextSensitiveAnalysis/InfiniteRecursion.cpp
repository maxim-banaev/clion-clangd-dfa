#include <functional>

namespace {
    void test1() {
        test1();
    }

    void test2();

#define CALL_TEST() test2()

    void test2() {
        CALL_TEST(); // a is incremented twice
    }


    class InfiniteFoo {
    public:
        void bar() {
            this->bar();
        }
    };

    template<typename T>
    void test3(T t) {
        test3(t);
    }
}