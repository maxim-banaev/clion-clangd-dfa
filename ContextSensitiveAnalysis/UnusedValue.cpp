// summary: should be 23 warnings
// bugs:
// https://youtrack.jetbrains.com/issue/CPP-21720/guard-variable-detector-suppresses-DFA-too-aggressively
// https://youtrack.jetbrains.com/issue/CPP-38634/No-unused-value-inspection-fro-stdstring
// https://youtrack.jetbrains.com/issue/CPP-38636/No-unused-value-inspection-for-templated-variable

#include <string>
#include <vector>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantFunctionResult"
// ReSharper disable CppDFAConstantFunctionResult
#pragma ide diagnostic ignored "UnusedLocalVariable"
// ReSharper disable CppDFAUnreadVariable
#pragma ide diagnostic ignored "ConstantConditionsOC"
// ReSharper disable CppDFAConstantConditions

// ReSharper disable CppDeclaratorNeverUsed

// Local DFA
namespace unused_value {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
// ReSharper disable once CppDFAUnusedValue
int test0() {
  int a = 0;
  a = 1;
  return a;
}
#pragma clang diagnostic pop
int test1() {
  int a = 0; // warn here
  int a1{0}; // warn here
  a = 1;
  a1 = 1;
  return a + a1;
}

double test2() {
  double a = 0.1; // warn here
  double a1{0.2}; // warn here
  a = 1;
  a1 = 1;
  return a + a1;
}

bool test3() {
  auto a = false; // warn here
  auto b{false};  // warn here
  a = true;
  b = true;
  return a && b;
}

// https://youtrack.jetbrains.com/issue/CPP-38634/No-unused-value-inspection-for-stdstring-variable
std::string test4() {
  std::string a = "a"; // warn here
  std::string b{"b"};  // shouldn't warn here
  a = "_a";
  b = "_b";
  return a + b;
}

std::vector<int> test5() {
  std::vector v = {1, 2, 3}; // shouldn't warn here
  return {1, 2, 3};          // shouldn't warn here
}

// https://youtrack.jetbrains.com/issue/CPP-38636/No-unused-value-inspection-for-templated-variable
template <typename T> T test6() {
  T t = 0; // warn here
  t = 1;
  return t;
}

void test7() {
  auto a = 1.3F;   // warn here
  auto b = 1.3e19; // warn here
}

void test8() {
  int *a = nullptr;  // warn here
  void *b = nullptr; // warn here
}

void test9() {
  int a[] = {1, 233}; // warn here
}

void test10() {
  char p = '\0'; // warn here
}

[[maybe_unused]] int test11() {
  int a = 1; // shouldn't warn here
  if (a > 0) {
    a = 2;
  }
  return a;
}
} // namespace unused_value

// Global DFA
namespace {
int test1() {
  int a = 0; // warn here
  int a1{0}; // warn here
  a = 1;
  a1 = 1;
  return a + a1;
}

double test2() {
  double a = 0.1; // warn here
  double a1{0.2}; // warn here
  a = 1;
  a1 = 1;
  return a + a1;
}

bool test3() {
  auto a = false; // warn here
  auto b{false};  // warn here
  a = true;
  b = true;
  return a && b;
}

// https://youtrack.jetbrains.com/issue/CPP-38634/No-unused-value-inspection-for-stdstring-variable
std::string test4() {
  std::string a = "a"; // warn here
  std::string b{"b"};  // shouldn't warn here
  a = "_a";
  b = "_b";
  return a + b;
}

std::vector<int> test5() {
  std::vector v = {1, 2, 3}; // shouldn't warn here
  return {1, 2, 3};          // shouldn't warn here
}

// https://youtrack.jetbrains.com/issue/CPP-38636/No-unused-value-inspection-for-templated-variable
template <typename T> T test6() {
  T t = 0; // warn here
  t = 1;
  return t;
}

void test7() {
  auto a = 1.3F;   // warn here
  auto b = 1.3e19; // warn here
}

void test8() {
  int *a = nullptr;  // warn here
  void *b = nullptr; // warn here
}

void test9() {
  int a[] = {1, 233}; // warn here
}

int test10() {
  int a = 1; // shouldn't warn here
  if (a > 0) {
    a = 2;
  }
  return a;
}
} // namespace

void checkGlobalDFA() {
  test1();
  test2();
  test3();
  test4();
  test5();
  ::test6<int>();
  test7();
  test8();
  test9();
  test10();
}

#pragma clang diagnostic pop