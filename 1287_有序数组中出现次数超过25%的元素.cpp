#include <vector>
#define INVALID -1
class Solution {
private:
  int computeLength(const std::vector<int> &arr, int idx) {
    int low = idx;
    int high = arr.size();
    const int &ele = arr[idx];
    while (low < high) {
      int middle = (low + high) / 2;
      if (arr[middle] == ele) {
        low = middle + 1;
      } else {
        high = middle;
      }
    }
    return low - idx;
  }

public:
  int findSpecialInteger(std::vector<int> &arr) {
    int length = arr.size();
    int vaildLength = arr.size() / 4 + 1;
    for (int i = 0; i < length;) {
      int curLength = computeLength(arr, i);
      if (curLength >= vaildLength) {
        return arr[i];
      }

      i += curLength;
    }

    // invalid
    return INVALID;
  }
};

#include <iostream>
int main() {
  Solution s;
  std::vector<int> input{1, 1};
  int k = s.findSpecialInteger(input);

  std::printf("%d\n", k);
  return 0;
}