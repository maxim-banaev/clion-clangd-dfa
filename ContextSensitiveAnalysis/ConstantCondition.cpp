// summary: should be 49 warnings
// bugs:
// https://youtrack.jetbrains.com/issue/CPP-17805/clangd-DFA-doesnt-work-when-Macro-is-used

#include <iostream>

#include <type_traits>
#pragma clang diagnostic push
// ReSharper disable CppDFAUnreadVariable
// ReSharper disable CppDFAUnusedValue
#pragma clang diagnostic ignored "-Wconstant-evaluated"
#pragma ide diagnostic ignored "ConstantParameter"
// ReSharper disable CppDFAConstantParameter
#pragma ide diagnostic ignored "UnreachableCode"
// ReSharper disable CppDFAUnreachableCode
#pragma ide diagnostic ignored "ConstantFunctionResult"
// ReSharper disable CppDFAConstantFunctionResult
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"

// ReSharper disable CppClassNeedsConstructorBecauseOfUninitializedMember
// ReSharper disable CppUninitializedNonStaticDataMember
// ReSharper disable StdIsConstantEvaluatedWillAlwaysEvaluateToConstant
// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement
// ReSharper disable CppVariableCanBeMadeConstexpr
// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable CppCompileTimeConstantCanBeReplacedWithBooleanConstant
// ReSharper disable CppTooWideScope
// ReSharper disable CppLocalVariableMayBeConst
// ReSharper disable CppCStyleCast
// ReSharper disable CppIfCanBeReplacedByConstexprIf

// Local DFA

#ifdef _MSC_VER
#pragma ide diagnostic ignored "cert-msc50-cpp"
#define random rand
#endif

namespace constant_condition {
void test() {
  int a = 1;
  if (a == 1) { //Condition is always true
  }

  // check the suppressing
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantConditionsOC"
  // ReSharper disable once CppDFAConstantConditions
  if (a != 0) {
  }
#pragma clang diagnostic pop
}

#define A(index) a == 1

void test1() {
  int a = 1;
  if (A(a)) { // https://youtrack.jetbrains.com/issue/CPP-17805/clangd-DFA-doesnt-work-when-Macro-is-used
  }
}

// negative case
void test2() {
  int a = 0;
  int b = 0;

  int *a_ptr = &a;
  *a_ptr = 1; // Modifies a, now a=1, b=0.

  if (a != b) { // shouldn't warn here
  }
}

// negative case
void test3() {
  int first = 0;
  int last = 0;

  std::cin >> first >> last;

  if (first == last) { // shouldn't warn here
  }
}

template <typename T> void test4();

template <> void test4<int>() {
  int t1 = 0;
  int t2 = 0;
  if (t1 == t2) { //Condition is always true
  }
}

void test5() {
  int *i = nullptr;
  if (i == nullptr) { //Condition is always true
  }

  std::string *s = nullptr;
  if (s == nullptr) { //Condition is always true
  }
}

typedef int X;

void test6() {
  X i = 1;
  if (i == 1) { //Condition is always true
  }
}

#define X 1
#define Y y

void test7() {
  int x = 1;
  int y = 1;

  if (x == X) { //Condition is always true
  }
  if (X == x) {
  } // https://youtrack.jetbrains.com/issue/CPP-17805/clangd-DFA-doesnt-work-when-Macro-is-used
  if (Y ==
      1) { // https://youtrack.jetbrains.com/issue/CPP-17805/clangd-DFA-doesnt-work-when-Macro-is-used
  }
  if (1 == Y) { //Condition is always true
  }
  if (x == Y) { //Condition is always true
  }
  if (Y ==
      x) { // https://youtrack.jetbrains.com/issue/CPP-17805/clangd-DFA-doesnt-work-when-Macro-is-used
  }
  if (Y ==
      X) { // https://youtrack.jetbrains.com/issue/CPP-17805/clangd-DFA-doesnt-work-when-Macro-is-used
  }
  if (X ==
      Y) { // https://youtrack.jetbrains.com/issue/CPP-17805/clangd-DFA-doesnt-work-when-Macro-is-used
  }
}

void test8() {
  float f = 0.5;
  if (f == 0.5) { //Condition is always true
  }
}

[[maybe_unused]] void test8_1() {
  float f = 0.5f;
  if (f == 0.5f) { //Condition is always true
  }
}

bool test9(int p1, [[maybe_unused]] int p2) {
  if (p1 == 1 || p1 == 2)
    return p1 == 1 || p1 == 2; //Condition is always true
  return false;
}

void fn(bool cond);
void test10() {
  int x = 1;
  fn(x == 1); //Condition is always true
}

void test11() {
  int x = 1;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
  [[maybe_unused]] bool a = x == 1; //Condition is always true
#pragma clang diagnostic pop
}

class [[maybe_unused]] test12 {
  int x;

public:
  [[maybe_unused]] void func() {
    this->x = 1;
    if (this->x == 1) { //Condition is always true
    }
  }
};

class [[maybe_unused]] test12_1 {
  void foo() {}

public:
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-undefined-compare"
  [[maybe_unused]] void bar() {
    if (this != nullptr) //Condition is always true
      foo();
  }
#pragma clang diagnostic pop
};

void test13() {
  int a = 1;
  [[maybe_unused]] auto cond = a == 1; //Condition is always true
}

void fn14([[maybe_unused]] bool flag = false) {}
void test14() {
  int a = 1;
  fn14(a == 1); //Condition is always true
}

int fn15() { return 0; }

void test15() {
  int a = 1;
  if (a == fn15()) { //Condition is always false
  }
}

[[maybe_unused]] void test16(bool flag) {
  int x = 1;
  [[maybe_unused]] bool a = flag ? x == 1 : x == 2; // warn here twice
}

// std::is_constant_evaluated is not covered by DFA.
// In Clion Classic it was covered by Simplify inspection
void test17() {
  if (std::is_constant_evaluated()) {
  }
}

[[maybe_unused]] void test17_1() {
  if constexpr (std::is_constant_evaluated()) {
  }
}

[[maybe_unused]] void test18() {
  [[maybe_unused]] const int n =
      std::is_constant_evaluated() ? 13 : 17;
}

template <int x> struct C {};

template <> struct C<true> {
  static const int x = 1;
};

template <> struct C<false> {
  static const int x = 0;
};

[[maybe_unused]] constexpr void test19([[maybe_unused]] const int x) {
  // Type checker correctly evaluates std::is_constant_evaluated() == true here
  if (C<std::is_constant_evaluated()>::x) {
  }
}

[[maybe_unused]] void test20() {
  int a = 1;
  if (a < 2) { //Condition is always true
  }
}

// negative case
[[maybe_unused]] void CPP_28958() {
  bool state = false;
  for (int i = 0; i < 10; ++i) {
    if (state) { // shouldn't warn here
      std::cout << "true\n";
    }
    state = !state;
  }
}

// negative case
static int verbose = 1;
[[maybe_unused]] static void *ptr = &verbose;
[[maybe_unused]] void CPP_29088() {
  if (verbose) // shouldn't warn here
    std::cout << "unknown \n";
}

// negative case
[[maybe_unused]] void *ptr1 = &verbose;
[[maybe_unused]] void CPP_29088_1() {
  if (verbose) // shouldn't warn here
    std::cout << "unknown \n";
}

int tenOrFive() { return random() ? 5 : 10; }
[[maybe_unused]] void CPP_30291(int y) {
  int x = tenOrFive();
  if (y < x) {
    if (y == 5) {
    } // shouldn't warn here
  }
}

static int x_cpp_26296;
void foo_cpp_26296() { x_cpp_26296 = 1; }
void bar_cpp_26296(void (*f)()) { f(); }

// negative case
int CPP_26296() {
  if (x_cpp_26296 != 0)
    return 1;
  bar_cpp_26296(foo_cpp_26296); // shouldn't warn here
  if (x_cpp_26296 != 1)
    return 1;
  return 0;
}

// negative case
[[maybe_unused]] int CPP_30449(int x, int y) {
  int big = abs(x) > abs(y) ? x : y;
  if (x == big) // shouldn't warn here
    return 1;
  return 0;
}

// negative case
void CPP_36723(const char *str) {
  for (const char *str_p = str;; str_p++) {
    char ch = *str_p;
    switch (ch) { // NOLINT(*-multiway-paths-covered)
    case ' ':
    case '\t':
    case '\n':
    case '\0':
      if (ch == '\n' || ch == '\0') { // shouldn't warn here
        return;
      }
      std::cout << "reached\n";
    }
  }
}

// negative case
void change_int(int *pInt) {
  *pInt = 1;
}
[[maybe_unused]] void CPP_36562() {
  int int1 = 0;
  int int2 = int1;
  change_int(&int2);
  if(int1 != int2) { // shouldn't warn here
    std::cout << "Integer was changed to: " << int2 << "\n";
  }
}

// negative case
[[maybe_unused]] const char* CPP_36559() {
  auto reply = "WTF?";
  if (((size_t)reply) < 0xFFFFFFFF) // shouldn't warn here
    return nullptr;
  return reply;
}

// negative case
[[maybe_unused]] void CPP_37944() {
  std::string_view sw{nullptr, 0};
  if (sw.data()) { // shouldn't warn here

  }
}
} // namespace constant_condition

// Global DFA
namespace {
void test() {
  int a = 1;
  if (a == 1) { //Condition is always true
  }

  // check the suppressing
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantConditionsOC"
  if (a != 0) { //Condition is always true
  }
#pragma clang diagnostic pop
}

#define A(index) a == 1

void test1() {
  int a = 1;
  if (A(a)) { // https://youtrack.jetbrains.com/issue/CPP-17805/clangd-DFA-doesnt-work-when-Macro-is-used
  }
}

// negative case
void test2() {
  int a = 0;
  int b = 0;

  int *a_ptr = &a;
  *a_ptr = 1; // Modifies a, now a=1, b=0.

  if (a != b) { // shouldn't warn here
  }
}

// negative case
void test3() {
  int first = 0;
  int last = 0;

  std::cin >> first >> last;

  if (first == last) { // shouldn't warn here
  }
}

template <typename T> void test4();

template <> void test4<int>() {
  int t1 = 0;
  int t2 = 0;
  if (t1 == t2) { //Condition is always true
  }
}

void test5() {
  int *i = nullptr;
  if (i == nullptr) { //Condition is always true
  }

  std::string *s = nullptr;
  if (s == nullptr) { //Condition is always true
  }
}

typedef int X1;

void test6() {
  X1 i = 1;
  if (i == 1) { //Condition is always true
  }
}

#define X 1
#define Y y

void test7() {
  int x = 1;
  int y = 1;

  if (x == X) { //Condition is always true
  }
  if (X ==
      x) { // https://youtrack.jetbrains.com/issue/CPP-17805/clangd-DFA-doesnt-work-when-Macro-is-used
  }
  if (Y ==
      1) { // https://youtrack.jetbrains.com/issue/CPP-17805/clangd-DFA-doesnt-work-when-Macro-is-used
  }
  if (1 == Y) { //Condition is always true
  }
  if (x == Y) { //Condition is always true
  }
  if (Y ==
      x) { // https://youtrack.jetbrains.com/issue/CPP-17805/clangd-DFA-doesnt-work-when-Macro-is-used
  }
  if (Y ==
      X) { // https://youtrack.jetbrains.com/issue/CPP-17805/clangd-DFA-doesnt-work-when-Macro-is-used
  }
  if (X ==
      Y) { // https://youtrack.jetbrains.com/issue/CPP-17805/clangd-DFA-doesnt-work-when-Macro-is-used
  }
}

int getZero() {
  int a = 0;
  return a;
}

int getOne() {
  int a = 1;
  return a;
}

void test8() {
  if (getZero() == 0) { //Condition is always true
  }
  if (getZero()) { //Condition is always false
  }
  if (!getZero()) { //Condition is always true
  }
  if (getZero( //Condition is always false
               // foo
          )) {
  }

  if (false) { // warn here
    asm("nop");
  } else if (getZero()) { //Condition is always false
  }
}

void test9() {
  while (getZero()) { //Condition is always false
  }
}

// negative case
int test10() {
  return 0;
  if (getZero() == 0) {
  } // shouldn't warn here
}

void test11() {
  if (getZero() == 0) { //Condition is always true
  }
  if (1 == getOne()) { //Condition is always true
  }
  if (getZero() == getOne()) { //Condition is always false
  }
}

bool test12(int p1, [[maybe_unused]] int p2) {
  if (p1 == 1 || p1 == 2)      //Condition is always true when reached
    return p1 == 1 || p1 == 2; //Condition is always true
  return false;
}

void fn([[maybe_unused]] bool cond) {}
void test13() {
  int x = 1;
  fn(false);
  fn(x == 1); //Condition is always true
}

void test14() {
  int x = 1;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
  [[maybe_unused]] auto b = x == 1; //Condition is always true
#pragma clang diagnostic pop
}

void test15() {
  int a = 1;
  [[maybe_unused]] auto cond = a == 1; //Condition is always true
}

void fn16([[maybe_unused]] bool flag = false) {}
void test16() {
  int a = 1;
  fn16();
  fn16(a == 1); //Condition is always true
}

int fn17() { return 0; }

void test17() {
  int a = 1;
  if (a == fn17()) { //Condition is always false
  }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantParameter"
void test18(float f = 0.f) {
  [[maybe_unused]] auto cond = f == 0.f; //Condition is always true
}
#pragma clang diagnostic pop

void test19() {
  if (std::is_constant_evaluated()) {
  }
}

// negative case
constexpr int test20([[maybe_unused]] bool flag) {
  if (std::is_constant_evaluated()) { // shouldn't warn here
    return 1;
  } else {
    return 0;
  }
}

[[maybe_unused]] void test21() {
  int a = 1;
  if (a < 2) { //Condition is always true
  }
}

// negative case
void CPP_28958() {
  bool state = false;
  for (int i = 0; i < 10; ++i) {
    if (state) { // shouldn't warn here
      std::cout << "true\n";
    }
    state = !state;
  }
}

int CPP_23668(bool t) {
  if (t) // warn here ???
    return 0;
  return 1;
}

int tenOrFive() { return random() ? 5 : 10; }
[[maybe_unused]] void CPP_30291(int y) {
  int x = tenOrFive();
  if (y < x) {
    if (y == 5) { // shouldn't warn here
    }
  }
}

int x_cpp_26296;
void foo_cpp_26296() { x_cpp_26296 = 1; }
void bar_cpp_26296(void (*f)()) { f(); }

// negative case
int CPP_26296() {
  if (x_cpp_26296 != 0)
    return 1;
  bar_cpp_26296(foo_cpp_26296); // shouldn't warn here
  if (x_cpp_26296 != 1)
    return 1;
  return 0;
}

// negative case
void CPP_36723(const char *str) {
  for (const char *str_p = str;; str_p++) {
    char ch = *str_p;
    switch (ch) { // NOLINT(*-multiway-paths-covered)
    case ' ':
    case '\t':
    case '\n':
    case '\0':
      if (ch == '\n' || ch == '\0') { // shouldn't warn here
        return;
      }
      std::cout << "reached\n";
    }
  }
}

// negative case
const char* CPP_36559(const char *reply) {
  if (((size_t)reply) < 0xFFFFFFFF)  // shouldn't warn here
    return nullptr;
  return reply;
}
} // namespace

void checkGlobalDFA() {
  test();
  test1();
  test2();
  test3();
  ::test4<int>();
  test5();
  test6();
  test7();
  test8();
  test9();
  test10();
  test11();
  test12(1, 2);
  test12(2, 1);
  test13();
  test14();
  test15();
  test16();
  test17();
  test18();
  test19();
  [[maybe_unused]] constexpr int f = test20(true);
  test21();

  CPP_28958();
  CPP_23668(0.0); // NOLINT(*-narrowing-conversions)
  CPP_30291(5);
  CPP_30291(6);
  CPP_26296();
  CPP_36723("\t");
  CPP_36559("WTF");
}
#pragma clang diagnostic pop