// summary: should be 8 warnings
#include <string>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "UnusedLocalVariable"
namespace {
    [[noreturn]] int test1() {} // warn here

    auto test2() -> bool {} // warn here

// https://youtrack.jetbrains.com/issue/CPP-17716
    template<typename T>
    int test3(T t) {}

#define func                                                                   \
  int test4() {}

    func // warn here

    class MissingFoo {
    public:
        std::string test5() {} // warn here

        static int test6() {} // warn here

        [[nodiscard]] int test7() const {} // warn here

        int test8();

        virtual int test9() = 0;
    };

    int MissingFoo::test8() {} // warn here

    class [[maybe_unused]] MissingBar : MissingFoo {
        int test9() override {} // warn here
    };
} // namespace
#pragma clang diagnostic pop