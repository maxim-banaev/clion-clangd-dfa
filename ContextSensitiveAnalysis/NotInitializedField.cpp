// summary: should be 6 warning
//bugs: to be done.
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantFunctionResult"
#pragma ide diagnostic ignored "UnusedValue"
#pragma ide diagnostic ignored "ConstantParameter"
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"

namespace {
struct test1 {
  int index;

public:
  void read_index() const { [[maybe_unused]] int value = index; } // warn here
  void increment_index() { index++; }                             // warn here
};

struct test1_1 {
  int index;

public:
  test1_1() = default;

  void check() { index++; } // warn here
};

struct test1_2 {
  int index{};

public:
  void check() { index++; } // shouldn't warn here. We use {}
};

struct test2 {
  [[maybe_unused]] int *buffer = new int[10];
  int index;

public:
  void add(int value) { buffer[index++] = value; } // warn here
};

template <typename T> struct test3 {
  T index;

public:
  void check() { index++; } // warn here
};

struct test4 {
  int index;

public:
  void setIndex(int ind) { test4::index = ind; }
  int getIndex() const {
    return index;
  } // shouldn't warn here. We use setter before.
};

struct test5 {
  int index : 5;

public:
  int getIndex() const { return index; } // warn here
};

struct test6 {
  int index;
  int getIndex() const {
    return index;
  } // shouldn't warn here. We initialize index before.
};

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