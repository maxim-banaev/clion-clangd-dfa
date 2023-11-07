// summary: should be 10 warnings
// bugs:
// https://youtrack.jetbrains.com/issue/CPP-25978/C-C-Data-flow-analysis-Loop-condition-isnt-updated-inside-the-loop-inspection-is-not-working-for-iterators
// https://youtrack.jetbrains.com/issue/CPP-34486/The-Loop-condition-inspection-stops-tracking-case-with-if-inside-the-loop
#include <vector>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
// ReSharper disable CppDFAUnreachableCode
#pragma ide diagnostic ignored "ConstantConditionsOC"
// ReSharper disable CppDFAConstantConditions
#pragma ide diagnostic ignored "EndlessLoop"
// ReSharper disable CppDFAEndlessLoop
#pragma ide diagnostic ignored "bugprone-suspicious-semicolon"
#pragma ide diagnostic ignored "ConstantParameter"
// ReSharper disable CppDFAConstantParameter
// Local DFA
namespace loop_condition {
void test1() {
  for (int i = 0; i < 10;) { // warn here
    if (i > 5)
      ;
  }
}

void test2(int a) {
  while (a < 10) { // warn here
  }
}

void test3(int a) {
  do {

  } while (a < 10); // warn here
}

void test4() {
  for (auto i = 0; i < 10;) { // warn here
  }
}

void test5(int i = 0) {
  for (; i < 10;) { // warn here
  }
}

// https://youtrack.jetbrains.com/issue/CPP-25978/C-C-Data-flow-analysis-Loop-condition-isnt-updated-inside-the-loop-inspection-is-not-working-for-iterators
void test6(const std::vector<int> &v) {
  for (auto wrapIter = v.begin(); wrapIter != v.end();) {
  }
}
} // namespace loop_condition

// Global DFA
namespace {
void test1() {
  for (int i = 0; i < 10;) { // warn here
    if (i > 5)
      ; // code
  }
}

void test2(int a) {
  while (a < 10) { // warn here
  }
}

void test3(int a) {
  do {

  } while (a < 10); // warn here
}

void test4() {
  for (int i = 0; i < 10;) { // warn here
  }
}

void test5(int i = 0) {
  for (; i < 10;) { // warn here
  }
}

// https://youtrack.jetbrains.com/issue/CPP-25978/C-C-Data-flow-analysis-Loop-condition-isnt-updated-inside-the-loop-inspection-is-not-working-for-iterators
void test6(const std::vector<int> &v) {
  for (auto wrapIter = v.begin(); wrapIter != v.end();) {
  }
}

// https://youtrack.jetbrains.com/issue/CPP-34486/The-Loop-condition-inspection-stops-tracking-case-with-if-inside-the-loop
void test7(int c) {
  int a = 10;
  while (a > 0) { // should warn here
    if (c > 0) {
      a--;
    }
  }
}
} // namespace

void checkGlobalDFA() {
  test1();
  test2(2);
  test3(3);
  test4();
  test5();
  test6({6});
  test7(-1);
}

#pragma clang diagnostic pop