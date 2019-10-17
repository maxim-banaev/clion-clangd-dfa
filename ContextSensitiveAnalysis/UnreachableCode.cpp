#include <iostream>

namespace {
void test() {
  return;
  int i_am_unreachable;
}

void test1() {
  while (true) {
  }

  int i_am_unreachable;
}

void test2() {
foo:
  int a = 1;

  if (a == 1)
    goto foo;

  int i_am_unreachable;
}

void test3(int a = 1) {
  switch (a) {
  case 1:
    std::cout << "1";
    break;
  case 2:
    std::cout << "2";
    break;
    int i_am_unreachable;
  default:
    std::cout << "hz";
    break;
  }
}

void test4(bool a) {
  std::string str = (a || true) ? "reachable" : "i_am_unreachable";
}

void test5() {
  while (false) {
    int i_am_unreachable;
  }
}

void test6() {
  int x = 0;
  if (true || false)
    x++;
  else
    int i_am_unreachable;
}

void test7() {
  for (int i = 0; i < 100; ++i) {
    continue;
    int i_am_unreachable;
  }

  for (int i = 0; i < 100; ++i) {
    break;
    int i_am_unreachable;
  }
}

template <typename T>
T test8() {
  T t;
  return t; T t1;
}
} // namespace