// summary: 11 warnings

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantConditionsOC"
#pragma ide diagnostic ignored "Simplify"

#include <iostream>
#include <mutex>
#include <string>

namespace unused_field {
class test1 {
  int _test1_1;  // warn here
  bool _test1_2; // warn here
  std::string _test1_3;

  char _test1_4; // shouldn't warn here
public:
  [[maybe_unused]] [[nodiscard]] char getTest1() const { return _test1_4; }

  [[maybe_unused]] void setTest1(char test1) { _test1_4 = test1; }
};

class test2 {
  static int _test2_1; // warn here
};

struct test3 {
  const int _test3_1; // warn here
};

struct test4 {
  [[maybe_unused]] int _test4_1; // shouldn't warn here
};

struct test5 {
  struct inner_struct_1 {};
  inner_struct_1 test5_1; // warn here

  struct inner_struct_2 {
    virtual ~inner_struct_2() = default;
  };
  inner_struct_2 test5_2; // shouldn't warn here

  struct inner_struct_3 {
    virtual ~inner_struct_3() = delete;
  };
  inner_struct_3 test5_3; // shouldn't warn here

  struct inner_struct_4 {
    inner_struct_4() = default;
  };
  inner_struct_4 test5_4; // warn here
};

struct test6 {
  int test6_1; // warn here that field is only assigned.

  explicit test6(int test61) : test6_1(test61) {}
};

struct test7 {
  int test7_1{}; // warn here

  test7() = default;
};

struct test8 {
  int test8_1{}; // warn here

  test8() = delete;
};

struct test9 {
  int test9_1{}; // warn here

  virtual ~test9() = default;
};

struct [[maybe_unused]] test10 {
  int test10_1{}; // warn here

  ~test10() { std::cout << "foo"; }
};

struct [[maybe_unused]] test11 {
  std::lock_guard<std::mutex> _lock;

public:
  [[maybe_unused]] explicit test11(std::mutex &mtx) : _lock(mtx) {}
};

struct base {
  int _test12; // shouldn't warn here
};
struct [[maybe_unused]] test12 : private base {
  [[maybe_unused]] void fn() { _test12 = 1; }

  [[maybe_unused]] int fn2() { return _test12; }
};

struct [[maybe_unused]] test13 {
  int _test13_1; // shouldn't warn here
  int _test13_2; // shouldn't warn here

  [[maybe_unused]] static int fn(test13 *t) { return t->_test13_1; };
  [[maybe_unused]] [[nodiscard]] int fn2() const { return this->_test13_2; };
};

} // namespace unused_field

#pragma clang diagnostic pop