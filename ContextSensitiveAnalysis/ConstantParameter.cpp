// summary: should be 25 warnings
// Constant parameter is working only with int-convertible types
// It's not working with other types even int() operator is defined
// https://youtrack.jetbrains.com/issue/CPP-23268/Constant-function-arguments-inspection-support-for-arguments-which-are-converted-in-inside-function-call
#include <climits>
#include <string>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-value"
#pragma ide diagnostic ignored "UnreachableCode"
// ReSharper disable CppDFAUnreachableCode
#pragma ide diagnostic ignored "ConstantConditionsOC"
// ReSharper disable CppDFAConstantConditions
#pragma ide diagnostic ignored "UnusedParameter"
// ReSharper disable CppDFAUnusedParameter
#pragma ide diagnostic ignored "UnusedValue"
// ReSharper disable CppDFAUnusedValue
#pragma ide diagnostic ignored "ConstantFunctionResult"
// ReSharper disable CppDFAConstantFunctionResult
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "UnusedLocalVariable"
// ReSharper disable CppDFAUnreadVariable
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"

// check the suppressing
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantParameter"
// ReSharper disable once CppDFAConstantParameter
void static test0(int a) {}
#pragma clang diagnostic pop

void static test000(bool cond) {
  int *x = nullptr;
  if (cond) {
    x = new int(20);
  }
  for (int i = 0; i < 10; i++) {
    if (cond) {
      *x; // Pointer may be null
    }
  }
}


void static test1(int a) {} // warn here

void static test2(const int &a) {} // look like is not working also

void static test3(const std::string &s) {}

void static test4(const int p) {} // warn here

void static test5(bool flag) {} // warn here

template <typename T> void static test6(T t) {} // warn here

enum Color { Blue = 0 };
enum class Letter { A = 0 };

void static test7(Color c,     // warn here
                  Letter l) {} // warn here

void static test8(float a) {}   // warn here
void static test8_1(float a) {} // warn here

typedef int MyInt;
void static test9(MyInt a) {} // warn here

void static test10(float f) {}    // warn here
void static test10_1(float f) {}  // warn here
void static test10_2(double d) {} // warn here

namespace {
void test11(int a) {}           // warn here
void test11_1(int a = 0) {}     // warn here
void test11_2(int a, int b) {}  // warn here
void test11_3(char c, int a) {} // warn here

void test12() {}

template <typename T> void test15(T t) {} // warn here

template <typename T, typename U>
void test16(T t,          // warn here
            U u = '.') {} // warn here

void test17(const int numbers...) {} // warn here
} // namespace

int static CPP_23668(bool t) { // shouldn't warn here
  if (t)
    return 1;
  return 0;
}

class X {
  [[maybe_unused]] static int zero;
  bool flag;

  void XTest1(unsigned p) {} // warn here

  static unsigned XTest2(unsigned p) { // warn here
    return p;
  }

public:
  void checkDFA() {
    XTest1(1);
    auto ret = flag ? XTest2(1) : 0;
  }
};

struct [[maybe_unused]] point {
  int x;
  int y;
};

static void CPP_23268(int a) {} // warn here

class one {
  int number;
public:
  explicit one(int n) : number(n) {}
  explicit operator int() const {
    return number;
  }
};

// negative case
static void CPP_29313(auto n) { // shouldn't warn here
}

void checkGlobalDFA() {
  test0(1);
  test1(1);
  test2(2);
  test3("3");
  test4(4);
  test5(true);
  test6(1);
  test7(Blue, Letter::A);
  test8(0.5);
  test8_1(0.5f);
  test9(9);
  test10(10.5);
  test10_1(10.5f);
  test10_2(123.456e-67);

  test11(INT_MAX);
  test11_1(0);
  test11_2(0, 1);
  test11_3('_', 1);

  test15<int>(0);
  test16<int, char>(1);
  test17(1, 2);

  CPP_23668(0.0);
  CPP_23268(static_cast<int>(0.5));
  one a(1);
  CPP_23268(static_cast<int>(1));
  CPP_23268(static_cast<int>(a));

  CPP_29313(1);
  CPP_29313(true);
}
#pragma clang diagnostic pop