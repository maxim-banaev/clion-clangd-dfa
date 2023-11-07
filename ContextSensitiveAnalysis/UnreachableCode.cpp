// summary: should be 39 warnings
// bugs: not yet found
#include <iostream>
#include <vector>

// Local DFA
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantFunctionResult"
// ReSharper disable CppDFAConstantFunctionResult
#pragma ide diagnostic ignored "LoopDoesntUseConditionVariableInspection"
#pragma ide diagnostic ignored "Simplify"
#pragma ide diagnostic ignored "ConstantParameter"
// ReSharper disable CppDFAConstantParameter
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "UnusedLocalVariable"
#pragma ide diagnostic ignored "UnusedValue"
// ReSharper disable CppDFAUnusedValue
// ReSharper disable CppDFAUnreadVariable
#pragma ide diagnostic ignored "ConstantConditionsOC"
// ReSharper disable CppDFAConstantConditions
#pragma ide diagnostic ignored "EndlessLoop"
// ReSharper disable CppDFAEndlessLoop
#pragma ide diagnostic ignored "hicpp-multiway-paths-covered"
namespace null_dereferences {
void test() {
  return;
  int i_am_unreachable; // warn here
}

[[noreturn]] void test1() {
  while (true) {
  }

  int i_am_unreachable; // warn here
}

void test2() {
foo:
  int a = 1;

  if (a == 1)
    goto foo;

  [[maybe_unused]] int i_am_unreachable; // warn here
}

void test3(int a = 1) {
  switch (a) {
  case 1:
    std::cout << "1";
    break;
  case 2:
    std::cout << "2";
    break;
    int i_am_unreachable; // warn here
  default:
    std::cout << "hz";
    break;
  }
}

void test4(bool flag) {
  std::string str =
      (flag || true) ? "reachable" : "i_am_unreachable"; // warn here
}

void test5() {
  while (false) {
    int i_am_unreachable; // warn here
  }
}

void test6() {
  int x = 0;
  if (true || false) // warn here
    x++;
  else
    int i_am_unreachable; // warn here
}

void test7() {
  for (int i = 0; i < 100; ++i) {
    continue;
    int i_am_unreachable; // warn here
  }

  for (int i = 0; i < 100; ++i) { // warn here
    break;
    int i_am_unreachable; // warn here
  }

  for (int i = 0; i < 100; ++i) { // warn here
    return;
    int i_am_unreachable; // warn here
  }
}
void test7_1() {
  std::vector<int> range = {1, 2, 3};
  for (const auto &item : range) {
    continue;
    int i_am_unreachable; // warn here
  }

  for (const auto &item : range) {
    break;
    int i_am_unreachable; // warn here
  }

  for (const auto &item : range) {
    return;
    int i_am_unreachable; // warn here
  }
}

template <typename T> T test8() {
  T t;
  return t;
  T t1; // warn here
}

class never_happens : public std::exception {};

void test9() {
  try {
    int a;
  } catch (never_happens &e) { // warn here
    int i_am_unreachable;
  }
}

// negative case
void test10() {
  try {
    int a;
  } catch (std::bad_alloc &e) {
    int i_am_not_unreachable; // shouldn't warn here.
  } catch (...) {
    int i_am_not_unreachable; // shouldn't warn here.
  }
}

// negative case
void test11() {
  try {
    int a = 1;
  } catch (...) {
    int i_am_not_unreachable; // shouldn't warn here.
  }
}

// negative case
void test12() {
  try {
    int a = 1;
  } catch (...) {
    int i_am_not_unreachable; // shouldn't warn here.
  }
}

// negative case
int CPP_30409(char c, int *mods) {
  if (c >= 'a' && c <= 'z') {
    return c - 'a' + 1;
  }
  *mods = 0;
  switch (c) {
  case '0':
    return 0;
  case ' ': // shouldn't warn here.
    return 2;
  }
  return 0;
}

constexpr bool foo() { return !std::is_constant_evaluated(); }

[[maybe_unused]] int CPP_31942() {
  if constexpr (foo()) {
    return 0; // warn here
  } else {
    return 1; // shouldn't warn here.
  }
}
} // namespace null_dereferences

// Global DFA
namespace {
void test() {
  return;
  int i_am_unreachable; // warn here
}

[[noreturn]] void test1() {
  while (true) {
  }

  int i_am_unreachable; // warn here
}

void test2() {
foo:
  int a = 1;

  if (a == 1)
    goto foo;

  int i_am_unreachable; // warn here
}

void test3(int a = 1) {
  switch (a) {
  case 1:
    std::cout << "1";
    break;
  case 2:
    std::cout << "2";
    break;
    int i_am_unreachable; // warn here
  default:
    std::cout << "hz";
    break;
  }
}

void test4(bool flag) {
  std::string str =
      (flag || true) ? "reachable" : "i_am_unreachable"; // warn here
}

void test5() {
  while (false) {
    int i_am_unreachable; // warn here
  }
}

void test6() {
  int x = 0;
  if (true || false) // warn here
    x++;
  else
    int i_am_unreachable; // warn here
}

void test7() {
  for (int i = 0; i < 100; ++i) {
    continue;
    int i_am_unreachable; // warn here
  }

  for (int i = 0; i < 100; ++i) { // warn here
    break;
    int i_am_unreachable; // warn here
  }

  for (int i = 0; i < 100; ++i) { // warn here
    return;
    int i_am_unreachable; // warn here
  }
}
void test7_1() {
  std::vector<int> range = {1, 2, 3};
  for (const auto &item : range) {
    continue;
    int i_am_unreachable; // warn here
  }

  for (const auto &item : range) {
    break;
    int i_am_unreachable; // warn here
  }

  for (const auto &item : range) {
    return;
    int i_am_unreachable; // warn here
  }
}

template <typename T> T test8() {
  T t{};
  return t;
  T t1; // warn here
}

class never_happens : public std::exception {};

void test9() {
  try {
    int a;
  } catch (never_happens &e) { // warn here
    int i_am_unreachable;
  }
}

// negative case
void test10() {
  try {
    int a;
  } catch (std::bad_alloc &e) {
    int i_am_not_unreachable; // shouldn't war here.
  } catch (...) {
    int i_am_not_unreachable; // shouldn't war here.
  }
}

// negative case
void test11() {
  try {
    int a = 1;
  } catch (...) {
    int i_am_not_unreachable; // shouldn't war here.
  }
}

constexpr bool foo() { return !std::is_constant_evaluated(); }

[[maybe_unused]] int CPP_31942() {
  if constexpr (foo()) {
    return 0; // warn here
  } else {
    return 1; // shouldn't warn here.
  }
}

} // namespace

void checkGlobalDFA() {
  test();
  test2();
  test3(1);
  test3(2);
  test3(3);
  test4(true);
  test5();
  test6();
  test7();
  test7_1();
  ::test8<int>();
  test9();
  test10();
  test11();
  CPP_31942();
  test1();
}
#pragma clang diagnostic pop