#include <stdio.h>
#include <math.h>

float test1() { // now no warning here
  float a = M_PI;
  return a;
}

double test2() { // warning still here
  double a = M_PI;
  return a;
}

int main() {
  printf("%d\n%d\n", test1() == M_PI, test2() == M_PI); //Prints "0 1"
  return 0;
}