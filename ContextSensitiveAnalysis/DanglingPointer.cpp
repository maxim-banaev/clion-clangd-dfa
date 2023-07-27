// summary: should be 2 warnings
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