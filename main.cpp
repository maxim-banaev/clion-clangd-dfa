#include <vector>

using int128_t = __int128;
using intpair = std::pair<int128_t,int128_t>;

int main() {

  std::vector<intpair> pairs;
  pairs.push_back({10, 20});
  pairs.push_back({20, 30});
  auto b = pairs[0].first;    // Subscripted value is not an array?!?!

  return 0;
}
