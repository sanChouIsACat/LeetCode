#include <algorithm>
#include <vector>

class Solution {
private:
  bool checkCanBePlaced(const std::vector<int> &position, int m, int distance) {
    int curIdx = 1;
    int preIdx = 0;
    int curCount = 1;
    while (curCount < m && curIdx < position.size()) {
      while (curIdx < position.size() &&
             position[curIdx] - position[preIdx] < distance)
        curIdx++;

      if (curIdx >= position.size()) {
        break;
      }

      curCount++;
      preIdx = curIdx;
      curIdx = preIdx + 1;
    }

    return curCount >= m;
  }

public:
  int maxDistance(std::vector<int> &position, int m) {
    std::sort(position.begin(), position.end());

    // left-closed, right-open interval
    int min = 1;
    int max = *position.rbegin() - *position.begin() + 1;

    while (min < max) {
      int middle = (min + max) / 2;

      if (checkCanBePlaced(position, m, middle)) {
        min = middle + 1;
      } else {
        max = middle;
      }
    }
    return min - 1;
  }
};

#include <iostream>
int main() {
  Solution s;
  std::vector<int> input{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::printf("%d\n", s.maxDistance(input, 4));
}