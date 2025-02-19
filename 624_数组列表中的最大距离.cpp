#include <climits>
#include <vector>

class Solution {
public:
  int maxDistance(std::vector<std::vector<int>> &arrays) {
    int length = arrays.size();
    int minEle = arrays[0][0];
    int maxEle = *arrays[0].rbegin();
    int res = 0;

    // compute min and max
    for (int i = 1; i < length; i++) {
      int curVecLength = arrays[i].size();
      const int &curMin = arrays[i][0];
      const int &curMax = arrays[i][curVecLength - 1];

      res = std::max(res, std::abs(curMax - minEle));
      res = std::max(res, std::abs(curMin - maxEle));

      if (curMin < minEle) {
        minEle = curMin;
      }
      if (curMax > maxEle) {
        maxEle = curMax;
      }
    }

    return res;
  }
};

#include <iostream>
int main() {
  //   std::vector<std::vector<int>> input{{1}, {1}};
  std::vector<std::vector<int>> input{{1, 2, 3}, {4, 5}, {1, 2, 3}};
  Solution s;
  std::printf("%d\n", s.maxDistance(input));
}