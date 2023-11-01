// summary: should be 8 warnings
// bugs:
// https://youtrack.jetbrains.com/issue/CPP-17805/clangd-DFA-doesnt-work-when-Macro-is-used
// https://youtrack.jetbrains.com/issue/CPP-17716/clangd-DFA-doesnt-work-when-template-is-used
#include <iostream>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantConditionsOC"
#pragma ide diagnostic ignored "ConstantParameter"
#pragma ide diagnostic ignored "misc-no-recursion"

// Local DFA
namespace infinite_recursion {
[[noreturn]] void test1() { test1(); } // warn here

void test2();

#define CALL_TEST() test2()

void test2() {
  CALL_TEST(); // https://youtrack.jetbrains.com/issue/CPP-17805/clangd-DFA-doesnt-work-when-Macro-is-used
}

// https://youtrack.jetbrains.com/issue/CPP-17716/clangd-DFA-doesnt-work-when-template-is-used
template <typename T> void test3(T t) { test3(t); }

void test4() {
  std::cout << "a";
  test4(); // warn here
}

void test5() {
  auto l = []() { test5(); };
  l();
}

class [[maybe_unused]] InfiniteFoo {
public:
  void test6() { this->test6(); } // warn here

  static void test7() { test7(); } // warn here

  void test8();

  void operator+() { this->operator+(); } // warn here
};

#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemberFunctionCanBeStatic"
void InfiniteFoo::test8() { test8(); } // warn here
#pragma clang diagnostic pop

void test9();
void test9_1();
void test9_2();

void test9() { test9_1(); }
void test9_1() { test9_2(); }
void test9_2() { test9(); }

void test10() {
  int a = 1;
  if (a > 0) {
    test10(); // should warn here
  }
}

} // namespace infinite_recursion

// Global DFA
namespace {
[[noreturn]] void test1() { test1(); } // warn here

void test2();

#define CALL_TEST() test2()

void test2() {
  CALL_TEST(); // https://youtrack.jetbrains.com/issue/CPP-17805/clangd-DFA-doesnt-work-when-Macro-is-used
}

// https://youtrack.jetbrains.com/issue/CPP-17716
template <typename T> void test3(T t) { test3(t); }

void test4() {
  std::cout << "a";
  test4(); // warn here
}

void test5() {
  auto l = []() { test5(); };
  l();
}

void test6() {
  int a = 1;
  if (a > 0) {
    test6(); // should warn here
  }
}
} // namespace

[[maybe_unused]] [[maybe_unused]] void checkGlobalDFA1() { test1(); }

[[maybe_unused]] void checkGlobalDFA2() { test2(); }

[[maybe_unused]] void checkGlobalDFA3() { ::test3<int>(1); }

[[maybe_unused]] void checkGlobalDFA4() { test4(); }

[[maybe_unused]] void checkGlobalDFA5() { test5(); }

[[maybe_unused]] void checkGlobalDFA6() { test6(); }
#pragma clang diagnostic pop