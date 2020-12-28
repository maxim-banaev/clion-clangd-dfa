// summary: should be 9 warnings
// Local DFA
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
namespace escape_analysis {
int *gPtr;
int g;

int *foo(int p) {
  int ar[3];
  int x = 0;
  int *ptr = &x;
  gPtr = ptr; // Address of local variable may escape the function
  gPtr = &x;  // Address of local variable may escape the function

  if (p == 1)
    return ptr; // Address of local variable may escape the function

  ptr = &g;
  gPtr = ptr;

  if (p == 2)
    return ptr;

  ptr = ar;
  gPtr = ptr; // Address of local variable may escape the function
  return ptr; // Address of local variable may escape the function
}
} // namespace

//Global DFA
namespace {
    int *gPtr;
    int g;

    int *foo(int p) {
        int ar[3];
        int x = 0;
        int *ptr = &x;
        gPtr = ptr; // Address of local variable may escape the function
        gPtr = &x;  // Address of local variable may escape the function

        if (p == 1)
            return ptr; // Address of local variable may escape the function

        ptr = &g;
        gPtr = ptr;

        if (p == 2)
            return ptr;

        ptr = ar;
        gPtr = ptr; // Address of local variable may escape the function
        return ptr; // Address of local variable may escape the function
    }
} // namespace


void checkGlobalDFA() {
    ::foo(0);
    ::foo(1);
    ::foo(2);
}
#pragma clang diagnostic pop