#include <vector>
using namespace std;
class Solution {
private:
  // informations about the duplicate array
  struct DuplicateInfos {
    // the index of the next element of the duplicate array
    unsigned int nextIdx;
    // the number of elements that are dumplicate
    unsigned int duplicateEleNum;
  };
  DuplicateInfos computeDuplicate(vector<int> &nums, unsigned int idx) {
    unsigned int duplicateNum = 1;
    for (unsigned int i = idx + 1; i < nums.size() && nums[i - 1] == nums[i];
         i++) {
      duplicateNum++;
    }
    return DuplicateInfos{idx + duplicateNum, duplicateNum};
  }
  void copyIfNecessary(vector<int> &nums, unsigned int dstIdx,
                       unsigned int srcIdx, unsigned int length) {
    for (unsigned int i = 0; i < length; i++) {
      nums[dstIdx + i] = nums[srcIdx + i];
    }
  }

public:
  int removeDuplicates(vector<int> &nums) {
    unsigned int newArrayCopyIdx = 0;
    for (unsigned int i = 0; i < nums.size();) {
      DuplicateInfos curDuplicate = computeDuplicate(nums, i);
      unsigned int newDuplicateArrayLen =
          curDuplicate.duplicateEleNum > 2 ? 2 : curDuplicate.duplicateEleNum;
      copyIfNecessary(nums, newArrayCopyIdx, i, curDuplicate.duplicateEleNum);
      newArrayCopyIdx += newDuplicateArrayLen;

      i += curDuplicate.duplicateEleNum;
    }

    // newArrayCopyIdx is updated to "to be filled", so now index is equal to
    // length
    return newArrayCopyIdx;
  }
};

#include <iostream>
void printVector(const std::vector<int> &nums) {
  std::cout << "nums = { ";
  for (size_t i = 0; i < nums.size(); ++i) {
    std::cout << nums[i];
    if (i < nums.size() - 1)
      std::cout << ", ";
  }
  std::cout << " }" << std::endl;
}
int main() {
  Solution s;
  vector<int> nums = {0, 0, 1, 1, 1, 1, 2, 3, 3};

  unsigned int newArrayLen = s.removeDuplicates(nums);
  printf("the new array length %d\n", newArrayLen);
  nums.resize(newArrayLen);
  printVector(nums);
}