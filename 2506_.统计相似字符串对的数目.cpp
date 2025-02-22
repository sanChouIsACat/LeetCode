#include <bitset>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
public:
  int similarPairs(std::vector<std::string> &words) {
    std::unordered_map<std::bitset<128>, unsigned int> cache;
    int sum = 0;
    for (auto &current : words) {
      std::bitset<128> key;
      for (auto &curChar : current) {
        key.set(curChar);
      }
      unsigned int &value = cache[key];
      sum += value++;
    }

    return sum;
  }
};

#include <iostream>
int main() {
  Solution s;
  std::printf("%d\n",
              s.similarPairs(std::vector<std::string>{"aabb", "ab", "ba"}));
  return 0;
}