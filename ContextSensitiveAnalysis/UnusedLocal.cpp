// summary: should be 24 warnings
// bugs:
// https://youtrack.jetbrains.com/issue/CPP-21720/guard-variable-detector-suppresses-DFA-too-aggressively
#include <iostream>
#include <unordered_map>
#include <vector>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wuninitialized"
#pragma ide diagnostic ignored "ConstantConditionsOC"
// ReSharper disable CppDFAConstantConditions
#pragma ide diagnostic ignored "UnreachableCode"
// ReSharper disable CppDFAUnreachableCode
#pragma ide diagnostic ignored "UnusedParameter"
// ReSharper disable CppDFAUnusedParameter
#pragma ide diagnostic ignored "UnusedValue"
// ReSharper disable CppDFAUnusedValue
#pragma ide diagnostic ignored "ConstantParameter"
// ReSharper disable CppDFAConstantParameter
#pragma ide diagnostic ignored "performance-unnecessary-value-param"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma clang diagnostic ignored "-Winvalid-noreturn"
#pragma ide diagnostic ignored "performance-for-range-copy"

// Local DFA
namespace unused_local {
// negative case
[[noreturn]] void test1() {
  int x = 0; // shouldn't warn here
  x++;
}

void test2(int x) {}

// negative case
void test3() {
  int x = 2; // shouldn't warn here
  x = x + 1;
}

class foo {
  int x;

public:
  static void test4(int x) { int y; } // warn here
};

void test5(foo f) { foo f1{}; } // warn here

void test6() { std::string s = "123"; } // shouldn't warn here

// https://youtrack.jetbrains.com/issue/CPP-21720/guard-variable-detector-suppresses-DFA-too-aggressively
void test7() {
  std::string s1;      // should warn here
  std::vector<int> v1; // should warn here
}

void test7_1(std::string s = "123") {}

template <typename T> void test8(T t) {}

void test9() {
  auto l = []() { // warn here
    int a;        // warn here
  };
}

void test9_1() {
  auto l = []() {}; // warn here
}

void test9_2() {
  auto l = [=]() {}; // warn here
}

void test9_3() {
  auto l = [&]() {}; // warn here
}

void test10() {
  float f = 0.3;  // warn here
  auto f1 = 0.4;  // warn here
  double d = 0.5; // warn here
}

// negative case
void test11() {
  int a = 1; // shouldn't warn here
  int b = 2;
  if (b < 0) {
    int d = a;
  }
}
template <typename T>
void CPP_30074(const std::unordered_map<std::string, T> &v) {
  for (auto item : v) { // shouldn't warn here
    std::cout << "\t\t - " << item.first;
  }
  // https://youtrack.jetbrains.com/issue/CPP-21720/guard-variable-detector-suppresses-DFA-too-aggressively
  for (auto item : v) { // should warn here
  }
}

void test12(const std::unordered_map<int, int> &v) {
  for (const auto item : v) {
  } // warn here
}

void test13(int c) {
  int &d = c; // warn here
}

// negative case
void *CPP_30354() {
  char *mem;             // shouldn't warn here
  size_t byteOffset = 8; // shouldn't warn here
  void *elements = (void *)&(mem[byteOffset]);
  return elements;
}
} // namespace unused_local

// Global DFA
namespace {
// negative case
[[noreturn]] void test1() {
  int x = 0; // shouldn't warn here
  x++;
}

void test2(int x) {}

// negative case
void test3() {
  int x = 2; // shouldn't warn here
  x = x + 1;
}

class foo {
  int x;

public:
  static void test4(int x) { int y; } // warn here
};

void test5(foo f) { foo f1{}; } // warn here

void test6() { std::string s = "123"; } // shouldn't warn here

// https://youtrack.jetbrains.com/issue/CPP-21720/guard-variable-detector-suppresses-DFA-too-aggressively
void test7(std::string s, std::vector<int> v) {
  std::string s1;      // should warn here
  std::vector<int> v1; // should warn here
}

void test7_1(std::string s = "123") {}

template <typename T> void test8(T t) {}

void test9() {
  auto l = []() { // warn here
    int a;        // warn here
  };
}

void test9_1() {
  auto l = []() {}; // warn here
}

void test9_2() {
  auto l = [=]() {}; // warn here
}

void test9_3() {
  auto l = [&]() {}; // warn here
}

void test10() {
  float f = 0.3;  // warn here
  auto f1 = 0.4;  // warn here
  double d = 0.5; // warn here
}

void test11() {
  int a = 1; // shouldn't warn here
  int b = 2;
  if (b < 0) {
    int d = a;
  }
}

template <typename T>
void CPP_30074(const std::unordered_map<std::string, T> &v) {
  for (auto item : v) { // shouldn't warn here
    std::cout << "\t\t - " << item.first;
  }
  // https://youtrack.jetbrains.com/issue/CPP-21720/guard-variable-detector-suppresses-DFA-too-aggressively
  for (auto item : v) { // should warn here
  }
}

void test12(const std::unordered_map<int, int> &v) {
  for (const auto item : v) {
  } // warn here
}

void test13(int c) {
  int &d = c; // warn here
}

// negative case
void *CPP_30354() {
  char *mem;             // shouldn't warn here
  size_t byteOffset = 8; // shouldn't warn here
  void *elements = (void *)&(mem[byteOffset]);
  return elements;
}
} // namespace

void checkGlobalDFA() {
  test2(1);
  test3();
  foo::test4(1);
  test5({});
  test6();
  test7("_", {1});
  test7_1();
  test8(1);
  test9();
  test9_1();
  test9_2();
  test9_3();
  test10();
  test11();
  test12({{1, 2}});
  test13(2);
  ::CPP_30074<int>({{"foo", 1}});
  CPP_30354();
  test1();
}
#pragma clang diagnostic pop