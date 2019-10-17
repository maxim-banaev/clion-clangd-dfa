#include <string>
namespace {
void test() {
  int a;
  if (a > 1) {
  }
}

struct X {
  int myFoo;
};

int test1() {
  X x;
  return x.myFoo; // no 'not unitialized warning'
}

struct bla {
  double foo = 0;
};

bla test2() {
  bla out;
  return out;
}

void test3() {
  int a, b, c;
  for (a = 0; a < 1; a++) {
    c = a + 1;
  }
  b = c;
}

void test4() {
  int a;
  a++;
}

void test5() {
  int a, b;
  a = b;
}

void test6() {
  std::string s1, s2;
  s2 = s1;
}

template <typename T> T test7() {
  T t1, t2;
  t1 = t2;
  return t1;
}

} // namespace