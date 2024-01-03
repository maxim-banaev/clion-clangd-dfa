// summary: should be 19 warnings
// bugs:
// https://youtrack.jetbrains.com/issue/CPP-23438/Unreachable-call-of-function-The-inspection-is-not-working-for-templated-function

#include <string>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
// ReSharper disable CppDFAEndlessLoop
#pragma ide diagnostic ignored "bugprone-reserved-identifier"
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"
#pragma clang diagnostic ignored "-Wtautological-undefined-compare"
#pragma ide diagnostic ignored "Simplify"
#pragma ide diagnostic ignored "OCUnusedStructInspection"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "ConstantConditionsOC"
// ReSharper disable CppDFAConstantConditions
#pragma ide diagnostic ignored "ConstantParameter"
// ReSharper disable CppDFAConstantParameter
#pragma ide diagnostic ignored "UnreachableCode"
// ReSharper disable CppDFAUnreachableCode

static void test1_function() {} // warn here

void test1() {
  if (false)
    test1_function();
}

static void test2_function() {} // warn here

void static test2(bool d = false) {
  if (d)
    test2_function();
}

void call_test2() { test2(); }

enum Switcher { ON, OFF };

static void test3_function() {} // warn here

void static test3(Switcher s = OFF) {
  switch (s) {
  case ON:
  case OFF:
    break;
  default:
    test3_function();
    break;
  }
}

void call_test3() { test3(); }

class Test4 {
  void test4_function() {} // warn here

public:
  void test4() {
    if (this == nullptr)
      test4_function();
  }
};

class Base {
  virtual void test5_function(){};
};

class Test5 : public Base {
  void test5_function() override {} // shouldn't warn here
public:
  void test5() {
    bool a = false;
    if (a)
      test5_function();
  }
};

namespace {
bool flag = false;

void test6_function() {} // warn here

void test6() {
  if (flag)
    test6_function();
}

std::string test7_function() { return ""; } // warn here

void test7() {
  if (flag)
    test7_function();
}

// https://youtrack.jetbrains.com/issue/CPP-23438/Unreachable-call-of-function-The-inspection-is-not-working-for-templated-function
// clangd limitation :(
template <typename T> void test8_function() {} // should warn here

template <typename T> void test8() {
  if (flag)
    test8_function<T>();
}
} // namespace

class Test9 {
  static void test9_function() {} // warn here

public:
  void test9() {
    if (flag)
      test9_function();
  }
};

static void test10_function() {} // warn here

#define _FUNC_NAME test10_function

void test10() {
  if (flag)
    _FUNC_NAME();
}

static void test11_function();

static void test11_function() {} // warn here

void test11() {
  if (flag)
    test11_function();
}

static void test12_function() {} // warn here

void do_nothing() {}

void test12() { flag ? test12_function() : do_nothing(); }

static void test13_function() {} // shouldn't warn here

void test13() {
  try {
  } catch (...) {
    test13_function();
  }
}

static void test14_function() {} // warn here

void test14() {
  return;
  test14_function();
}

static void test14_1_function() {} // warn here

void test14_1() {
  while (true) {
    break;
    test14_1_function();
  }
}

static void test14_2_function() {} // warn here

void test14_2() {
  for (int a = 1; a < 5; a++) {
    continue;
    test14_2_function();
  }
}

static void test15_function() {} // warn here

void test15() {
  while (true) {
  }
  test15_function();
}

static void test16_function() {} // warn here

void test16() {
  goto test16_label;
  test16_function();
test16_label:
  return;
}

static bool test17_function() { return true; } // warn here

void test17() {
  if (!flag || test17_function()) {
    do_nothing();
  }
}

static bool test18_function() { return true; } // warn here

void test18() {
  if (!flag) {
    do_nothing();
  } else if (test18_function()) {
  }
}

static bool test19_function() { return true; } // warn here

void test19() {
  if (flag && test19_function()) {
    do_nothing();
  }
}

static bool test20_function() { return true; } // warn here

void test20([[maybe_unused]] int a) {
  for (int i = 0; true || test20_function(); i++) {
  }
}

void checkGlobalDFA() {
  test6();
  test7();
  ::test8<int>();
}
#pragma clang diagnostic pop