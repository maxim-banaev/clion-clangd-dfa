#include <iostream>

namespace {
void test1() { test1(); }

void test2();

#define CALL_TEST() test2()

// https://youtrack.jetbrains.com/issue/CPP-17805
void test2() {
  CALL_TEST(); // a is incremented twice
}

// https://youtrack.jetbrains.com/issue/CPP-17716
template <typename T> void test3(T t) { test3(t); }

// https://youtrack.jetbrains.com/issue/CPP-17578#focus=streamItem-27-3733783.0-0
// as designed. Functions may throw an exception and end a caller function.
void test4() {
  std::cout << "a";
  test4();
}

void test5() {
  auto l = []() { test5(); };
  l();
}

class InfiniteFoo {
public:
  void test6() { this->test6(); }

  static void test7() { test7(); }

  void test8();

  void operator+() { this->operator+(); }
};

#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemberFunctionCanBeStatic"
void InfiniteFoo::test8() { InfiniteFoo::test8(); }
#pragma clang diagnostic pop

void test9();
void test9_1();
void test9_2();

void test9() { test9_1(); }
void test9_1() { test9_2(); }
void test9_2() { test9(); }

} // namespace