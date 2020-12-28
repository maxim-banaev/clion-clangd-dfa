#include <string>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma clang diagnostic ignored "-Winvalid-noreturn"
namespace {
    std::string something;

    [[noreturn]] void test1() {
        char val[100];
        something = val;
    }
} // namespace
#pragma clang diagnostic pop