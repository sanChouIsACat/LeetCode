#include <vector>
class Solution {
public:
  std::vector<int> evenOddBit(int n) {
    // not include highest mask
    std::vector<int> ans;
    ans.resize(2);
    int offset = 0;

    for (int i = 0; i < 31; i++, offset = (offset + 1) % 2) {
      ans[offset] += n & 1;
      n = n >> 1;
    }

    return ans;
  }
};

#include <iostream>
int main() {
  Solution s;
  std::vector<int> ans = s.evenOddBit(2);
  std::printf("%d %d\n", ans[0], ans[1]);
  return 0;
}