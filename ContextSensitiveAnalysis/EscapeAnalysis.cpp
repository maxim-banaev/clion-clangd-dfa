// summary: should be 11 warnings
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
// Local DFA
namespace escape_analysis {
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
} // namespace

//Global DFA
namespace {
    int *gPtr;
    int g;

    int *foo(int p) {
        int ar[3];
        int x = 0;
        int *ptr = &x;
        // https://youtrack.jetbrains.com/issue/CPP-23550
        gPtr = ptr; // should warn here
        gPtr = &x;  // warn here

        if (p == 1)
            return ptr; // warn here

        ptr = &g;
        gPtr = ptr;

        if (p == 2)
            return ptr;

        ptr = ar;
        // https://youtrack.jetbrains.com/issue/CPP-23550
        gPtr = ptr; // should warn here
        return ptr; // warn here
    }
} // namespace


void checkGlobalDFA() {
    ::foo(0);
    ::foo(1);
    ::foo(2);
}
#pragma clang diagnostic pop