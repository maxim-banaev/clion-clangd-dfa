#include <string>
namespace {
    int test1() {}

    template<typename T>
    int test2(T t){}

#define INT int

    INT test3() {}

#define func int test4() {}
    func

    class EscapeFoo {
    public:

        EscapeFoo();

        std::string test5() {}

        static int test6() {}

        [[nodiscard]] int test7() const {}

        int test8();
    };

    int EscapeFoo::test8() {}

    EscapeFoo::EscapeFoo() = default;
}