#include <climits>
#include <vector>

class Solution {
public:
  std::vector<int> replaceElements(std::vector<int> &arr) {
    std::vector<int> ret;
    // concer case check
    if (arr.empty()) {
      return ret;
    }

    // init
    std::vector<int> max;
    int length = arr.size();
    max.resize(length);
    ret.resize(length);

    // compute max cache
    max[length - 1] = arr[length - 1];
    for (int i = length - 2; i >= 0; i--) {
      max[i] = max[i + 1] > arr[i] ? max[i + 1] : arr[i];
    }

    // fill value
    for (int i = 0; i < length - 1; i++) {
      ret[i] = max[i + 1];
    }
    ret[length - 1] = -1;

    // return
    return ret;
  }
};

#include <iostream>
int main() {
  Solution s;
  std::vector<int> input{17, 18, 5, 4, 6, 1};
  auto ans = s.replaceElements(input);

  for (auto ele : ans) {
    std::cout << ele << " ";
  }
  return 0;
}