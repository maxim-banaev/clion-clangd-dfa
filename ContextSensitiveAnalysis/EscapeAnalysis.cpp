// summary: should be 15 warnings
// bugs:
// https://youtrack.jetbrains.com/issue/CPP-23550/Dangling-pointers-Address-of-local-variable-may-escape-the-function-is-not-detected
#include <cstdlib>
#include <string>
#include <vector>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantParameter"
// ReSharper disable CppDFAConstantParameter
#pragma ide diagnostic ignored "DanglingPointer"
// ReSharper disable CppDFADeletedPointer
#pragma ide diagnostic ignored "UnusedValue"
// ReSharper disable CppDFAUnusedValue
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
// Local DFA
namespace escape_analysis {
int *gPtr;
int g;

int *test(int p) {
  int ar[3];
  int x = 0;
  int *ptr = &x;
  gPtr = ptr; // warn here
  gPtr = &x;  // warn here

  if (p == 1)
    return ptr; // warn here

  ptr = &g;
  gPtr = ptr;

  if (p == 2)
    return ptr;

  ptr = ar;
  gPtr = ptr; // warn here
  return ptr; // warn here
}

int *create_array() { return (int *)malloc(100 * sizeof(int)); }

// negative case
void CPP_29550() {
  for (int i = 0; i < 100; ++i) {
    int *arr = create_array();
    free(arr); // shouldn't warn here
  }
}

// negative case
void CPP_29840(std::string &out) {
  // false positive
  std::vector<std::string> v;
  out = v[0]; // shouldn't warn here
}

// negative case
const char *CPP_35738() {
  return ""; // shouldn't warn here
}

struct Wrapper {
  const char *Ptr;
};

Wrapper create() {
  char Arr[2];
  Arr[0] = 'A';
  Arr[1] = '\0';
  return Wrapper{Arr}; // warn here
}

void test2() {
  Wrapper w{};
  w.Ptr = "";
}

class MyClass {};

const MyClass &foo(const MyClass &c) { return c; }

const MyClass &test3(const MyClass &param, bool flag) {
  MyClass local;

  if (flag)
    return foo(param);
  else
    return foo(local); // warn here
}

struct Holder {
  int *ref;
};

struct Wrapper1 {
  Holder holder;

  void saveString(int *block) { holder.ref = block; }
};

Wrapper1 globalWrapper;

Wrapper1 test(Wrapper1 &paramWrapper) {
  int p;
  Wrapper1 localWrapper1{};
  Wrapper1 localWrapper2{};

  localWrapper1.saveString(&p);

  localWrapper2.saveString(&p);

  paramWrapper.saveString(&p);  // warn here
  globalWrapper.saveString(&p); // warn here
  return localWrapper2;         // warn here
}

// negative case
std::string CPP_35947(size_t size) {
  char value[size];
  return {value}; // shouldn't warn here
}

} // namespace escape_analysis

// Global DFA
namespace {
int *gPtr;
int g;

int *foo(int p) {
  int ar[3];
  int x = 0;
  int *ptr = &x;

  gPtr = ptr; // warn here
  gPtr = &x;  // warn here

  if (p == 1)
    return ptr; // warn here

  ptr = &g;
  gPtr = ptr;

  if (p == 2)
    return ptr;

  ptr = ar;

  gPtr = ptr; // warn here
  return ptr; // warn here
}

int *create_array() { return (int *)malloc(100 * sizeof(int)); }

// negative case
void CPP_29550() {
  for (int i = 0; i < 100; ++i) {
    int *arr = create_array();
    free(arr); // shouldn't warn here
  }
}

// negative case
void CPP_29840(std::string &out) {
  // false positive
  std::vector<std::string> v;
  out = v[0]; // shouldn't warn here
}

// negative case
const char *CPP_35738() {
  return ""; // shouldn't warn here
}

// negative case
std::string CPP_35947(size_t size) {
  char value[size];
  return {value}; // shouldn't warn here
}
} // namespace

void checkGlobalDFA() {
  foo(0);
  foo(1);
  foo(2);

  CPP_29550();
  std::string out;
  CPP_29840(out);
  CPP_35738();
  CPP_35947(10);
}
#pragma clang diagnostic pop