// summary: should be 18 warnings
#include <functional>
#include <string>

#ifndef _MSC_VER
#include <unistd.h>
#endif

// Local DFA
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "UnusedValue"
#pragma ide diagnostic ignored "OCUnusedStructInspection"
#pragma ide diagnostic ignored "UnusedLocalVariable"
#pragma ide diagnostic ignored "misc-no-recursion"
#pragma ide diagnostic ignored "ConstantConditionsOC"
#pragma ide diagnostic ignored "ConstantParameter"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"

#ifdef _MSC_VER
#pragma ide diagnostic ignored "cert-msc50-cpp"
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#define sleep _sleep
#define random rand
#endif


namespace constant_function_result {

// check the suppressing
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantFunctionResult"
bool test0() {
  int a = 0;
  return a;
}
#pragma clang diagnostic pop

// https://youtrack.jetbrains.com/issue/CPP-23365
bool test1() { return true; }

// https://youtrack.jetbrains.com/issue/CPP-23365
bool test1_2() { return true; }

int test2() { // warn here
  int a = 0;
  return a;
}

char test3() { // warn here
  auto a = 'c';
  return a;
}

float test4() { // warn here
  float a = 1.1;
  return a;
}

double test4_1() { // warn here
  float a = 1.1f;
  return a;
}

double test4_2() { // warn here
  double a = 1.1;
  return a;
}

enum class Letter { A };

Letter test5() { // warn here
  Letter l = Letter::A;
  return l;
}

// https://youtrack.jetbrains.com/issue/CPP-23490
bool test11() {
  auto a = true;
  auto b = false;
  return a && b;
}
} // namespace constant_function_result

// Global DFA
namespace {
// https://youtrack.jetbrains.com/issue/CPP-23365
bool test1() { return true; }

bool test1_1(int x, bool b = true) { // warn here
  if (x > 0)
    return b;
  return true;
}

auto test1_2(int x, bool b = true) -> bool { // warn here
  if (x > 0)
    return b;
  return true;
}

// It seems that inspection is working only with int-convertible types
std::string test2(int x, std::string s = "") {
  if (x % 2 == 0)
    return s;
  sleep(x);
  return "";
}

char test3(int x, char c = '3') { // warn here
  if (x % 2 == 0)
    return c;
  sleep(x);
  return '3';
}

auto test4(int x, int b = 0) -> decltype(1) { // warn here
  if (x > 0)
    return b;
  return 0;
}

template <int N> int test5(int x, int b = N) { // warn here
  if (x > 0)
    return b;
  return N;
}

// https://youtrack.jetbrains.com/issue/CPP-23449
template <typename T> T test6(T x, T b = 0) {
  if (x > 0)
    return b;
  return 0;
}

enum class Letter { A, B [[maybe_unused]] };

Letter test7(int x, Letter l = Letter::A) { // warn here
  if (x > 0)
    return l;
  return Letter::A;
}

// https://youtrack.jetbrains.com/issue/CPP-23378
int test8(int x) {
  if (random() % 2 == 0)
    return test8(x);
  return x;
}

void *test9(int x, void *p = nullptr) { // warn here
  if (x > 0)
    return p;
  return nullptr;
}

// https://youtrack.jetbrains.com/issue/CPP-23379
int test10(int x, int b = 0) {
  if (x > 0)
    return b;
  return 0;
}

// https://youtrack.jetbrains.com/issue/CPP-23490
bool test11() {
  auto a = true;
  auto b = false;
  return a && b;
}
} // namespace

// https://youtrack.jetbrains.com/issue/CPP-23365
static bool test15() { return true; }

class X {
  static int number;

  static int test16(int offset) { // warn here
    return offset;
  }

  static int test17(int offset) { // warn here
    if (offset == 0) {
      return number;
    } else {
      return 1;
    }
  }

public:
  void
  check_test16() { // NOLINT(readability-convert-member-functions-to-static)
    int tmp = test16(0);
  }

  void
  check_test17() { // NOLINT(readability-convert-member-functions-to-static)
    int tmp = test17(0);
  }
};

int X::number = 0;

static float test18(int x, float b = 0.17) { // warn here.
  if (x > 0)
    return b;
  return 0.17;
}

static float test18_1(int x, float b = 0.17f) { // warn here.
  if (x > 0)
    return b;
  return 0.17f;
}

static double test18_2(int x, double b = 0.17) { // warn here.
  if (x > 0)
    return b;
  return 0.17;
}

static bool CPP_23668(double t) { // should warn here?
  return t;
}

void checkGlobalDFA() {
  test1();
  test1_1(1);
  test1_2(1);
  test2(2);
  test3(3);
  test4(4);
  ::test5<0>(5);
  ::test6<int>(6);
  test7(7);
  test8(8);
  test9(9);

  std::function<int(int, int)> f_test10 = test10;
  f_test10(10, 0);
  test11();

  test15();

  X x;
  x.check_test16();
  x.check_test17();

  test18(18);
  test18_1(18);
  test18_2(18);

  CPP_23668(0.0);
}

#pragma clang diagnostic pop