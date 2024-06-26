// summary: should be 31 warnings in Classic | 33 warnings in Nova
// bugs:
// https://youtrack.jetbrains.com/issue/CPP-38639/The-same-endless-do-while-loop-is-warned-twice-in-CLion-Nova
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedTemplateParameterInspection"
#pragma ide diagnostic ignored "UnreachableCallsOfFunction"
// ReSharper disable CppDFAUnreachableCallsOfFunction
#pragma ide diagnostic ignored "LoopDoesntUseConditionVariableInspection"
// ReSharper disable CppDFALoopConditionNotUpdated
#pragma ide diagnostic ignored "Simplify"
#pragma ide diagnostic ignored "ConstantConditionsOC"
// ReSharper disable CppDFAConstantConditions
#pragma ide diagnostic ignored "ConstantParameter"
// ReSharper disable CppDFAConstantParameter
#pragma ide diagnostic ignored "ConstantFunctionResult"
// ReSharper disable CppDFAConstantFunctionResult
#pragma ide diagnostic ignored "UnreachableCode"
// ReSharper disable CppDFAUnreachableCode
#pragma ide diagnostic ignored "UnusedLocalVariable"

// ReSharper disable CppDeclaratorNeverUsed
// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement

// Local DFA
#include <iostream>
namespace endless_loop {
void test1() {
  for (;;) { // warn here
  }
}

void test1_1() {
  for (;;) // warn here
    int a;
}

void test1_2() {
  for (;;) { // warn here
    int a;
    int b;
  }
}

[[noreturn]] void test2() {
  for (;;) {
    int a;
  } // shouldn't be there
}

void test3() {
  while (true) { // warn here
  }
}

void test3_1() {
  while (true) // warn here
    int a;
}

void test3_2() {
  while (true) { // warn here
    int a;
    int b;
  }
}

void test4() {
  do {
  } while (true); // warn here
}

void test4_1() {
  do {
    int a;
  } while (true); // warn here
}

void test4_2() {
  do
    int a;
  while (true); // warn here
}

void test5() {
foo:
  int a; // warn here
  goto foo;
}

void test5_1() {
foo:
  goto foo; // warn here
}

void test5_2() {
foo:
  int a; // warn here
  goto bar;
  int i_am_unused;
bar:
  int b; // warn here
  goto foo;
}

template <typename T> void test6() {
  while (true) { // warn here
  }
}

// negative case
void test7() {
  for (int i = 0; i < 3; i++) { // shouldn't warn here
  }
}

void test8() {
  int a = 1;
  while (a > 0) { // warn here
  }
}

void code() {
  std::cout << "reached\n";
}

void CPP_32820() {
  for (int i = 0; i < 3; i++) { // shouldn't warn here
    switch (i) {} // NOLINT(*-multiway-paths-covered)
    code();
  }
}
} // namespace endless_loop

// Global DFA
namespace {
void test1() {
  for (;;) { // warn here
  }
}

void test1_1() {
  for (;;) // warn here
    int a;
}

void test1_2() {
  for (;;) { // warn here
    int a;
    int b;
  }
}

[[noreturn]] void test2() {
  for (;;) {
    int a;
  } // shouldn't be there
}

void test3() {
  while (true) { // warn here
  }
}

void test3_1() {
  while (true) // warn here
    int a;
}

void test3_2() {
  while (true) { // warn here
    int a;
    int b;
  }
}

void test4() {
  do {
  } while (true); // warn here
}

void test4_1() {
  do {
    int a;
  } while (true); // warn here
}

void test4_2() {
  do
    int a;
  while (true); // warn here
}

void test5() {
foo:
  int a; // warn here
  goto foo;
}

void test5_1() {
foo:
  goto foo; // warn here
}

void test5_2() {
foo:
  int a; // warn here
  goto bar;
  int i_am_unused;
bar:
  int b; // warn here
  goto foo;
}

template <typename T> void test6() {
  while (true) { // warn here
  }
}

bool getTrue(bool a = true) { return a; }
void test7() {
  while (getTrue()) { // warn here
  }
}

// negative case
void test8() {
  for (int i = 0; i < 3; i++) { // shouldn't warn here
  }
}

[[maybe_unused]] void test9() {
  while (true) { // shouldn't warn here. No call of function
  }
}

void test10() {
  int a = 1;
  while (a > 0) { // warn here
  }
}

void code() {
  std::cout << "reached\n";
}

void CPP_32820() {
  for (int i = 0; i < 3; i++) { // shouldn't warn here
    switch (i) {} // NOLINT(*-multiway-paths-covered)
    code();
  }
}

} // namespace

[[maybe_unused]] void checkGlobalDFA() {
  test1();
  test1_1();
  test1_2();
  test3();
  test3_1();
  test3_2();
  test4();
  test4_1();
  test4_2();
  test5();
  test5_1();
  test5_2();
  ::test6<int>();
  test7();
  test8();
  test10();
  CPP_32820();
}

[[maybe_unused]] void checkGlobalDFA1() { test2(); }
#pragma clang diagnostic pop