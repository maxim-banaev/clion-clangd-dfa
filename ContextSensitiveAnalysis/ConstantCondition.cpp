#include <iostream>
#include <string>
namespace {
void test() {
  int a = 1;
  if (a == 1) { // Should be warn here
  }

  // check the suppressing
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantConditions"
  if (a != 0) { // Shouldn't be warn here
                // https://youtrack.jetbrains.com/issue/CPP-18857
  }
#pragma clang diagnostic pop
}

#define A(x) x == 1

void test1() {
  int a = 1;
  if (A(a)) { // Should warn here https://youtrack.jetbrains.com/issue/CPP-17805
  }
}

// https://youtrack.jetbrains.com/issue/CPP-3583
void test2() {
  int a = 0;
  int b = 0;

  int *a_ptr = &a;
  *a_ptr = 1; // Modifies a, now a=1, b=0.

  if (a != b) { // Shouldn't warn here
  }
}

// https://youtrack.jetbrains.com/issue/CPP-13000
void test3() {
  int first = 0;
  int last = 0;

  std::cin >> first >> last;

  if (first == last) { // Shouldn't be warn here
  }                    // Condition is always true
}

template <typename T> void test4();

template <> void test4<int>() {
  int t1 = 0;
  int t2 = 0;
  if (t1 == t2) { // Should be warn here
  }
}

void test5() {
  int *i = nullptr;
  if (i == nullptr) {
  } // Should be warn here

  std::string *s = nullptr;
  if (s == nullptr) {
  } // Should be warn here
}

typedef int X;
void test6() {
  X i = 1;
  if (i == 1) {
  } // Should be warn here
}

#define X 1
#define Y y
void test7() {
  int x = 1;
  int y = 1;

  if (x == X) {
  } // Should be warn here
  if (X == x) {
  } // Should be warn here
  if (Y == 1) {
  } // Should be warn here
  if (1 == Y) {
  } // Should be warn here
  if (x == Y) {
  } // Should be warn here
  if (Y == x) {
  } // Should be warn here
  if (Y == X) {
  } // Should be warn here
  if (X == Y) {
  } // Should be warn here
}

} // namespace