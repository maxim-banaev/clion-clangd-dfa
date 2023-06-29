// summary: should be 16 warnings
#include <functional>
#include <string>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedStructInspection"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "ConstantParameter"
#pragma ide diagnostic ignored "performance-unnecessary-value-param"
// Local DFA
namespace unused_parameter {
void test1(int p) {} // warn here

void test2(float p) {} // warn here

void test3(const std::string p) {} // warn here

void test4(int &p) {} // warn here

void test5(int *p) {} // warn here

void test6(std::function<int(void)> f) {} // warn here

template <typename T> void test7(T t) {} // warn here

void test8(const int numbers...) {} // warn here

enum class Letter { A };
void test9(Letter l) {} // warn here

// https://youtrack.jetbrains.com/issue/CPP-23537
void test10() {
  auto l = [](int p) {};

  l(1);
}

class X {
public:
  void test15(int p) {} // warn here

  void test11(int p) const {} // warn here

  static void test12(int p) {} // warn here
};
} // namespace unused_parameter

// Global DFA
namespace {
void test1(int p) {} // warn here

void test2(float p) {} // warn here

void test3(const std::string p) {} // warn here

void test4(int &p) {} // warn here

// https://youtrack.jetbrains.com/issue/CPP-23537
void test10() {
  auto l = [](int p) {};

  l(1);
}
} // namespace

void checkGlobalDFA() {
  test1(1);
  test2(2.0);
  test3("");
  int a{0};
  test4(a);
  test10();
}
#pragma clang diagnostic pop