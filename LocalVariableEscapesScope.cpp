#include <string>

namespace {
    std::string something;

    [[noreturn]] void test1() {
        char val[100];
        something = val;
    }
} // namespace