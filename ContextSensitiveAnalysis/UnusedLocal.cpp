#include <string>
#include <vector>

namespace {
void test1() {
  int x = 0;
  x++;
}

void test2(int x) {}

void test3() {
  int x = 2;
  x = x + 1;
}

class foo {
  int x;

public:
  static void test4(int x) { int y; }
};

void test5(foo f) { foo f1; }

void test6() { std::string s = "123"; }

void test7(std::string s, std::vector<int> v) {
  std::string s1;
  std::vector<int> v1;
}

template <typename T> void test8(T t) {}

} // namespace