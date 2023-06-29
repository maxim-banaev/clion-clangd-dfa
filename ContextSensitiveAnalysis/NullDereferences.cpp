// summary: should be 10 warnings

#include <string>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
#pragma ide diagnostic ignored "ConstantConditionsOC"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Winvalid-noreturn"
// local DFA
namespace null_dereference {
struct foo {
  char data[42];
};

[[noreturn]] size_t test1() {
  struct foo *t = nullptr;
  t->data;         // warn here
  sizeof(t->data); // shouldn't warn here
}

void test2(std::string *a, std::string b) {

  while (a != nullptr || a->length()) { // warn here
    a = &b;
  }

  std::string *a1 = nullptr;
  while (a1 == nullptr || a1->length()) { // shouldn't warn here
    a1 = &b;
  }
}

void test3() {
  bool *f = nullptr;
  char *c = nullptr;
  if (*f && *c) { // warn here twice
  }
}

void test4() {
  struct foo *t;
  int a = 1;
  if (a > 0) {
    t = nullptr;
  } else {
    t = new foo();
  }
  t->data; // warn here
}
} // namespace null_dereference

// global DFA
namespace {
struct foo {
  char data[42];
};

[[noreturn]] size_t test1() {
  struct foo *t = nullptr;
  t->data;         // warn here
  sizeof(t->data); // shouldn't warn here
}

void test2() {
  std::string *a = nullptr;
  std::string b = "a";

  while (a != nullptr || a->length()) { // warn here
    a = &b;
  }

  std::string *a1 = nullptr;
  while (a1 == nullptr || a1->length()) { // shouldn't warn here
    a1 = &b;
  }
}

void test3() {
  bool *f = nullptr;
  char *c = nullptr;
  if (*f && *c) { // warn here twice
  }
}

void test4() {
  struct foo *t;
  int a = 1;
  if (a > 0) {
    t = nullptr;
  } else {
    t = new foo();
  }
  t->data; // warn here
}

struct Base {
  virtual ~Base() = default;

  [[maybe_unused]] virtual void f(){};
};

struct Derived1 : public virtual Base {};
struct Derived2 : public virtual Base {};

class Test5 {
private:
  static void dynCastDereference(Base *a) {
    auto *b = dynamic_cast<Derived1 *>(a);
    *b; // Pointer may be null
  }

public:
  static void testDynamicCastBadConservativeCase() {
    auto *b = new Derived1();
    auto *b2 = dynamic_cast<Derived1 *>(b);
    *b2; // Pointer may be null
    dynCastDereference(b2);
  }

  static void testDynamicCastGoodCase() {
    auto *b = new Derived1();
    auto *b2 = dynamic_cast<Derived2 *>(b);
    *b2; // Pointer may be null
    dynCastDereference(b2);
  }
};

} // namespace
void checkGlobalDFA() {
  test2();
  test3();
  test4();
  Test5::testDynamicCastBadConservativeCase();
  Test5::testDynamicCastGoodCase();
  test1();
}
#pragma clang diagnostic pop