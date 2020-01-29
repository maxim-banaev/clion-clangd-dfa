#include <vector>
#include <iostream>

namespace {
void test() {
  return;
  int i_am_unreachable; // Should be warn here
}

void test1() {
  while (true) {
  }

  int i_am_unreachable; // Should be warn here
}

void test2() {
foo:
  int a = 1;

  if (a == 1)
    goto foo;

  int i_am_unreachable; // Should be warn here
}

void test3(int a = 1) {
  switch (a) {
  case 1:
    std::cout << "1";
    break;
  case 2:
    std::cout << "2";
    break;
    int i_am_unreachable; // Should be warn here
  default:
    std::cout << "hz";
    break;
  }
}

void test4(bool a) {
  std::string str = (a || true) ? "reachable" : "i_am_unreachable"; // Should be warn here
}

void test5() {
  while (false) {
    int i_am_unreachable; // Should be warn here
  }
}

void test6() {
  int x = 0;
  if (true || false) // Should be warn here
    x++;
  else
    int i_am_unreachable; // Should be warn here
}

void test7() {
  for (int i = 0; i < 100; ++i) {
    continue;
    int i_am_unreachable; // Should be warn here
  }

  for (int i = 0; i < 100; ++i) {
    break;
    int i_am_unreachable; // Should be warn here
  }

  for (int i = 0; i < 100; ++i) {
    return;
    int i_am_unreachable; // Should be warn here
  }

  std::vector<int> range = {1,2,3};
  for (const auto &item : range) {
    continue;
    int i_am_unreachable; // Should be warn here
  }

  for (const auto &item : range) {
    break;
    int i_am_unreachable; // Should be warn here
  }

  for (const auto &item : range) {
    return;
    int i_am_unreachable; // Should be warn here
  }
}

template <typename T> T test8() {
  T t;
  return t;
  T t1; // Should be warn here
}
} // namespace