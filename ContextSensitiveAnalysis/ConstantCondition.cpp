#include <iostream>

namespace {
void test() {
  int a = 1;
  if (a == 1) {
  }

  // check the suppressing
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantCondition"
  if (a != 0) {
  }
#pragma clang diagnostic pop
}

#define A(x) x == 1

void test1() {
  int a = 1;
  if (A(a)) {
  }
}

// https://youtrack.jetbrains.com/issue/CPP-3583
void test2() {
  int a = 0;
  int b = 0;

  int *a_ptr = &a;
  *a_ptr = 1; // Modifies a, now a=1, b=0.

  if (a != b) {
  }
}

// https://youtrack.jetbrains.com/issue/CPP-13000
void test3() {
  int first = 0;
  int last = 0;

  std::cin >> first >> last;

  if (first == last) {
  }; // Condition is always true
}

template <typename T> void test4();

template <> void test4<int>() {
  int t1 = 0;
  int t2 = 0;
  if (t1 == t2) {
  }
}
} // namespace