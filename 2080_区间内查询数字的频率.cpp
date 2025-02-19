#include <stdexcept>
#include <unordered_map>
#include <vector>

class RangeFreqQuery {
private:
  std::unordered_map<int, std::vector<int>> idxMap;
  int getNearestNum(std::vector<int> &arr, int value, int startIdx = 0) {
    int low = startIdx;
    int high = arr.size();

    while (low < high) {
      int middle = (low + high) / 2;
      int midELe = arr[middle];
      if (midELe < value) {
        low = middle + 1;
      } else {
        high = middle;
      }
    }
    return low;
  };

public:
  RangeFreqQuery(std::vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
      std::vector<int> &numIdxVec = idxMap[arr[i]];
      numIdxVec.emplace_back(i);
    }
  }

  int query(int left, int right, int value) {
    auto it = idxMap.find(value);
    if (it == idxMap.end()) {
      return 0;
    }
    std::vector<int> &numIdxVec = (*it).second;
    int count = 0;

    int l = getNearestNum(numIdxVec, left);
    int r = getNearestNum(numIdxVec, right, l);

    if (r == numIdxVec.size() || numIdxVec[r] > right) {
      return r - l;
    } else {
      return r - l + 1;
    }
  }
};

#include <iostream>
int main() {
  std::vector<int> input{12, 33, 4, 56, 22, 2, 34, 33, 22, 12, 34, 56};
  RangeFreqQuery s{input};
  std::printf("%d\n", s.query(1, 2, 4));
  std::printf("%d\n", s.query(0, 11, 33));
}