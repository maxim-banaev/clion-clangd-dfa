// summary: should be 3 warnings
// bugs:
// https://youtrack.jetbrains.com/issue/CPP-35884/stdlist-iterator-is-marked-as-invalid-after-the-list-modification

#include <list>
#include <iostream>
#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotInitializedField"

// local DFA
namespace dangling_pointer {
struct node {
  node *next;
};

void test1(node *head) {
  for (node *pt = head; pt != nullptr; pt = pt->next) { // warn here
    delete pt;
  }
}

// negative case
// https://youtrack.jetbrains.com/issue/CPP-35884/stdlist-iterator-is-marked-as-invalid-after-the-list-modification
void test2() {
  std::list list{1, 2, 3};
  auto it = list.begin();
  list.push_back(4);
  std::cout << *it; // shouldn't warn here
}
} // namespace dangling_pointer

// global DFA
namespace {
struct node {
  node *next;
};
void test1(node *head) {
  for (node *pt = head; pt != nullptr; pt = pt->next) { // warn here
    delete pt;
  }
}
} // namespace

void checkGlobalDFA() { test1(new node()); }
#pragma clang diagnostic pop