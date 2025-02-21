#include <climits>
#include <iostream>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

#define UN_FILLED INT_MAX
class Solution {
private:
  int queryCache(int i, int j, int carpetLen,
                 std::vector<std::vector<int>> &cache, std::string &floor) {
    int &ele = cache[i][j];
    if (ele != UN_FILLED) {
      return ele;
    }

    // state transfer function
    int a = queryCache(i - 1, j, carpetLen, cache, floor) + (floor[i] == '1');
    int b;
    // if current location i is less than carpet length, it's should be zero
    if (i - carpetLen < 0) {
      b = 0;
    } else {
      b = queryCache(i - carpetLen < 0 ? 0 : i - carpetLen, j - 1, carpetLen,
                     cache, floor);
    }
    ele = std::min(a, b);
    return ele;
  }

public:
  int minimumWhiteTiles(std::string floor, int numCarpets, int carpetLen) {
    int vecLength = floor.size();
    int colLength = numCarpets + 1;
    std::vector<std::vector<int>> cache;
    for (int i = 0; i < vecLength; i++) {
      cache.emplace_back(colLength, UN_FILLED);
    }

    if (numCarpets >= vecLength) {
      return 0;
    }

    // init cache
    for (int i = 1; i < colLength; i++) {
      cache[0][i] = 0;
    }
    int whiteBlockNum = 0;
    for (int i = 0; i < vecLength; i++) {
      whiteBlockNum += floor[i] == '1';
      cache[i][0] = whiteBlockNum;
    }

    // maybe manuall y recursion
    return queryCache(vecLength - 1, numCarpets, carpetLen, cache, floor);
    // return 0;
  }
};

int main() {
  Solution s;
  std::printf("%d\n", s.minimumWhiteTiles("11111", 2, 3));
  std::printf("%d\n", s.minimumWhiteTiles("10110101", 2, 2));
  return 0;
}