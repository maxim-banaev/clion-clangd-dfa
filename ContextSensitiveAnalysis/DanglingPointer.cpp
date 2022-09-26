// summary: 2 warnings

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