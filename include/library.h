#ifndef CLANGD_DFA_INSPECTION_CHECKER_LIBRARY_H
#define CLANGD_DFA_INSPECTION_CHECKER_LIBRARY_H

class [[maybe_unused]] test12_class {
public:
  [[nodiscard]] size_t test12() const { return _nports; } // shouldn't warn here
  [[maybe_unused]] void do_something();

private:
  size_t _nports = 0;
};

#endif // CLANGD_DFA_INSPECTION_CHECKER_LIBRARY_H
