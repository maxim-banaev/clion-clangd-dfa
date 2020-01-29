namespace {
void test1() {
  for (;;) {
  }
}

void test1_1() {
  for (;;)
    int a;
}

void test1_2() {
  for (;;) {
    int a;
    int b;
  }
}

[[noreturn]] void test2() {
  for (;;) {
    int a;
  } // should'n be there
}

_Noreturn void test2_1() {
  for (;;) {
    int a;
  } // should'n be there
}

void test3() {
  while (true) {
  }
}

void test3_1() {
  while (true)
    int a;
}

void test3_2() {
  while (true) {
    int a;
    int b;
  }
}

void test4() {
  do {
  } while (true);
}

void test4_1() {
  do {
    int a;
  } while (true);
}

void test4_2() {
  do
    int a;
  while (true);
}

void test5() {
foo:
  int a;
  goto foo;
}

void test5_1() {
foo:
  goto foo;
}

void test5_2() {
foo:
  int a;
  goto bar;
  int i_am_unused;
bar:
  int b;
  goto foo;
}

template <typename T> void test6() {
  while (true) {
  }
}

// check the suppressing
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

void test7() {
  for (;;) {
  }
}

#pragma clang diagnostic pop
} // namespace
