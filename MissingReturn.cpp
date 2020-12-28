#include <string>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "UnusedLocalVariable"
namespace {
    [[noreturn]] int test1() {}

    auto test2() -> bool {}

// https://youtrack.jetbrains.com/issue/CPP-17716
    template<typename T>
    int test3(T t) {}

#define func                                                                   \
  int test4() {}

    func

    class MissingFoo {
    public:
        std::string test5() {}

        static int test6() {}

        [[nodiscard]] int test7() const {}

        int test8();

        virtual int test9() = 0;
    };

    int MissingFoo::test8() {}

    class [[maybe_unused]] MissingBar : MissingFoo {
        int test9() override {}
    };
} // namespace
#pragma clang diagnostic pop