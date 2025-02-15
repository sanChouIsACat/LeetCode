#include <stdexcept>
#include <vector>

#define INVALID -1
#define SHOULD_GO_TO_RIGHT 1
#define SHOULD_GO_TO_LEFT -1
class Solution {
private:
  struct Coordinate {
    int x;
    int y;
  };

private:
  Coordinate toNextDir(const Coordinate &coor,
                       const std::vector<std::vector<int>> &grid) {
    int rowNum = grid.size();
    int colNum = grid[0].size();
    const int &x = coor.x;
    const int &y = coor.y;

    if (grid[x][y] == SHOULD_GO_TO_RIGHT && y < colNum - 1 &&
        grid[x][y + 1] == SHOULD_GO_TO_RIGHT) {
      return Coordinate{x + 1, y + 1};
    } else if (grid[x][y] == SHOULD_GO_TO_RIGHT &&
               (y == colNum - 1 || grid[x][y + 1] == SHOULD_GO_TO_LEFT)) {
      return Coordinate{x, -1};
    } else if (grid[x][y] == SHOULD_GO_TO_LEFT && y > 0 &&
               grid[x][y - 1] == SHOULD_GO_TO_LEFT) {
      return Coordinate{x + 1, y - 1};
    } else if (grid[x][y] == SHOULD_GO_TO_LEFT &&
               (y == 0 || grid[x][y - 1] == SHOULD_GO_TO_RIGHT)) {
      return Coordinate{x, -1};
    }
    return Coordinate{-1, -1};
  };

public:
  std::vector<int> findBall(std::vector<std::vector<int>> &grid) {
    std::vector<int> ret;
    if (grid.empty()) {
      return ret;
    }

    int rowNum = grid.size();
    int colNum = grid[0].size();
    for (int i = 0; i < colNum; i++) {
      Coordinate curCoor{0, i};
      while (curCoor.x < rowNum && curCoor.y != INVALID) {
        curCoor = toNextDir(curCoor, grid);
      }
      ret.push_back(curCoor.y);
    }

    return ret;
  }
};

#include <iostream>
int main() {
  //   std::vector<std::vector<int>> matrix = {{1, 1, 1, -1, -1},
  //                                           {1, 1, 1, -1, -1},
  //                                           {-1, -1, -1, 1, 1},
  //                                           {1, 1, 1, 1, -1},
  //                                           {-1, -1, -1, -1, -1}};
  //   std::vector<std::vector<int>> matrix = {{-1}};
  std::vector<std::vector<int>> matrix = {{1, 1, 1, 1, 1, 1},
                                          {-1, -1, -1, -1, -1, -1},
                                          {1, 1, 1, 1, 1, 1},
                                          {-1, -1, -1, -1, -1, -1}};

  Solution s;
  std::vector<int> ans = s.findBall(matrix);

  for (const auto &val : ans) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
}