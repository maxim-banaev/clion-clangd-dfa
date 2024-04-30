// summary: should be 8 warnings
// bugs: not yet found

#include <cstdlib>
#include <new>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
// ReSharper disable CppDFAUnreachableCode
#pragma ide diagnostic ignored "UnusedLocalVariable"
// ReSharper disable CppDFAUnreadVariable
#pragma ide diagnostic ignored "ConstantConditionsOC"
// ReSharper disable CppDFAConstantConditions
#pragma ide diagnostic ignored "ConstantParameter"
// ReSharper disable CppDFAConstantParameter
#pragma ide diagnostic ignored "UnusedValue"
// ReSharper disable CppDFAUnusedValue

// ReSharper disable CppDeclaratorNeverUsed

namespace memory_leak {
class MyClass {
  [[maybe_unused]] int *leakedField = new int; // warn here
};

void test1() {
  auto c = new MyClass;
  delete c;
}

void test2() {
  [[maybe_unused]] auto c = new int; // warn here
}

[[maybe_unused]] void test2_1() {
  [[maybe_unused]] auto c = new int[10]; // warn here
}

// negative case
void test3() {
  [[maybe_unused]] auto c = new int; // shouldn't warn here.
  delete c;
}

// negative case
void test4() {
  auto c = new int; // shouldn't warn here.
  free(c);
}

// negative case
void test5() {
  auto c = malloc(10); // shouldn't warn here.
  free(c);
}

void test6() {
  [[maybe_unused]] auto c = malloc(10); // warn here
}

void test7() {
  malloc(10); // shouldn't warn here.
}

void test8([[maybe_unused]] auto c = new int) {}

void test9(bool flag) {
  [[maybe_unused]] auto c = new int; // warn here
  if (flag)
    delete c;
}

void test10() {
  auto l = []() {
    [[maybe_unused]] auto c = new int; // warn here
  };
  l();
}

struct foo {};
void test11() {
  [[maybe_unused]] auto c = new foo; // warn here
}

#define NEW new

void test12() { [[maybe_unused]] auto c = NEW int; }

// negative case
int *alloc() {
  return new int(10); // shouldn't warn here.
}

[[maybe_unused]] void CPP_35968() {
  int *x = alloc(); // shouldn't warn here
  delete x;
}

} // namespace memory_leak

namespace {
void test(bool flag) {
  [[maybe_unused]] auto c = new int; // warn here
  if (flag)
    delete c;
}

// negative case
int *alloc() {
  return new int(10); // shouldn't warn here
}

// negative case
void CPP_35968() {
  int *x = alloc(); // shouldn't warn here
  delete x;
}

// negative case
struct Point { int x, y; };

[[maybe_unused]] void CPP_36129() {
  char buf[sizeof(Point)];
  auto *p = ::new (buf) Point; // shouldn't warn here
}
} // namespace

void checkGlobalDFA() {
  test(false);
  CPP_35968();
}
#pragma clang diagnostic pop