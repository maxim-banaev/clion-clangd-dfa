#include <string>

struct S {
  S(const S &) {}

  S() {}

  virtual ~S() {}
};

int main() {
  S s;
  S &s1 = s;
  S &&s2 = S();
  const std::string &rs = "abc";
  const double &rcd2 = 2;
  double &&rrd3 = 2;
}