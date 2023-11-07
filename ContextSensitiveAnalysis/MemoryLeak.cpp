// summary: should be 8 warnings
// bugs: not yet found
#include <cstdlib>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedLocalVariable"
// ReSharper disable CppDFAUnreadVariable
#pragma ide diagnostic ignored "ConstantConditionsOC"
// ReSharper disable CppDFAConstantConditions
#pragma ide diagnostic ignored "ConstantParameter"
// ReSharper disable CppDFAConstantParameter
#pragma ide diagnostic ignored "UnusedValue"
// ReSharper disable CppDFAUnusedValue
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

void test4() {
  auto c = new int; // shouldn't warn here.
  free(c);
}

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
    auto c = new int; // warn here
  };
  l();
}

struct foo {};
void test11() {
  [[maybe_unused]] auto c = new foo; // warn here
}

#define NEW new

void test12() {
  auto c = NEW int;
}

} // namespace memory_leak

namespace {
void test(bool flag) {
  [[maybe_unused]] auto c = new int; // warn here
  if (flag)
    delete c;
}
} // namespace

void checkGlobalDFA() { test(true); }
#pragma clang diagnostic pop