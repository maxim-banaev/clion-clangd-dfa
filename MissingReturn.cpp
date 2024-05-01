// summary: should be 15 warnings
// bugs:
// https://youtrack.jetbrains.com/issue/CPP-17716/clangd-DFA-doesnt-work-when-template-is-used

#include <map>
#include <memory>
#include <string>
#include <vector>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
// ReSharper disable CppDFAUnusedValue
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "UnusedLocalVariable"

// ReSharper disable CppDeclaratorNeverUsed
// ReSharper disable CppPolymorphicClassWithNonVirtualPublicDestructor
// ReSharper disable CppDFAUnreadVariable
// ReSharper disable CppNotAllPathsReturnValue

namespace {
[[noreturn]] int test1() {} // warn here

auto test2() -> bool {} // warn here

template <typename T> int test3([[maybe_unused]] T t) {} // warn here
template <> int test3([[maybe_unused]] int t) {} // warn here

#define func                                                                   \
  int test4() {}

func // warn here

    class MissingFoo {
public:
  std::string test5() {}                   // warn here
  std::vector<int> test5_1() {}            // warn here
  std::map<int, bool> test5_2() {}         // warn here
  std::shared_ptr<MissingFoo> test5_3() {} // warn here

  static int test6() {} // warn here

  [[nodiscard]] int test7() const {} // warn here

  int test8();

  virtual int test9() = 0;
};

int MissingFoo::test8() {} // warn here

class [[maybe_unused]] MissingBar : MissingFoo {
  int test9() override {} // warn here
};

void test10() {
  auto l = []() -> int {}; // warn here
}

int test11(bool flag) {
  if (flag)
    return 0;
} // warn here

int test11_1(int number) {
  switch (number) {
  case 1:
  case 2:
    return 0;
  default:
    break;
  }
} // warn here

// negative case
int test12() { return 1; }

} // namespace
#pragma clang diagnostic pop