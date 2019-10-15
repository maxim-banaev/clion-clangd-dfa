#include <string>


namespace {
    std::string something;

    void test1() {
        char val[100];
        something = val;
    }
}