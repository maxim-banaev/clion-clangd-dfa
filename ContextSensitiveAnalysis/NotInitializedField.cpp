// summary: should be 4 warning
// bugs:
// https://youtrack.jetbrains.com/issue/CPP-35830/C-C-Data-Flow-Analysis-Not-Initialized-Field-doesnt-work-if-structure-is-trivial-type
// https://youtrack.jetbrains.com/issue/CPP-35831/C-C-Data-Flow-Analysis-Not-Initialized-Field-doesnt-work-with-templated-type
//
// topics:
// https://timsong-cpp.github.io/cppwp/n4861/dcl.init#6
// https://en.cppreference.com/w/cpp/language/zero_initialization

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantFunctionResult"
// ReSharper disable CppDFAConstantFunctionResult
#pragma ide diagnostic ignored "UnusedValue"
// ReSharper disable CppDFAUnusedValue
// ReSharper disable CppDFAUnreadVariable
#pragma ide diagnostic ignored "ConstantParameter"
// ReSharper disable CppDFAConstantParameter
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"

// ReSharper disable CppExpressionWithoutSideEffects
// ReSharper disable CppDiscardedPostfixOperatorResult
// ReSharper disable CppClassNeedsConstructorBecauseOfUninitializedMember
// ReSharper disable CppUninitializedNonStaticDataMember

namespace {
struct test1 {
  void read_index() const { [[maybe_unused]] int value = index; } // warn here
  void increment_index() { index++; }                             // warn here
private:
  int index;
};

struct test1_1 {
  test1_1() = default;
  // https://youtrack.jetbrains.com/issue/CPP-35830/C-C-Data-Flow-Analysis-Not-Initialized-Field-doesnt-work-if-structure-is-trivial-type
  void check() { index++; } // should warn here
private:
  int index;
};

struct test1_2 {
  void check() { index++; } // shouldn't warn here. We use {}
private:
  int index{};
};

struct test2 {
  void add(int value) { buffer[index++] = value; } // warn here
private:
  [[maybe_unused]] int *buffer = new int[10];
  int index;
};

template <typename T> struct test3 {
  // https://youtrack.jetbrains.com/issue/CPP-35831/C-C-Data-Flow-Analysis-Not-Initialized-Field-doesnt-work-with-templated-type
  void check() { index++; } // shouldn't warn here. Works as expected.
private:
  T index;
};

struct test4 {
  void setIndex(int ind) { test4::index = ind; }
  int getIndex() const {
    return index; // shouldn't warn here. We use setter before.
  }
private:
  int index;
};

struct test5 {
  int getIndex() const { return index; } // warn here
private:
  int index : 5;
};

struct test6 {
  int index;
  int getIndex() const {
    return index; // shouldn't warn here. We initialize index before.
  }
};

// negative case
[[maybe_unused]] int CPP_36825() {
  struct S {
    struct {
      int x;
    };
  };

  S s = {1};
  return s.x; // shouldn't warn here.
}
} // namespace

[[maybe_unused]] void check() {
  test1 t1;
  t1.read_index();
  t1.increment_index();

  test1_1 t1_1 = test1_1();
  t1_1.check();

  test1_2 t1_2;
  t1_2.check();

  test2 t2;
  t2.add(1);

  test3<int> t3;
  t3.check();

  test4 t4;
  t4.setIndex(0);
  t4.getIndex();

  test5 t5;
  t5.getIndex();

  test6 t6;
  t6.index = 0;
  t6.getIndex();
}

#pragma clang diagnostic pop