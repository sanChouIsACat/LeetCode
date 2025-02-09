#include <iostream>
#include <stack>
#include <tuple>
#include <vector>

using namespace std;
#define NON_INIT -1
class Solution {
private:
  struct Coordinate {
    int x;
    int y;
  };

public:
  vector<vector<int>> buffer;

private:
  void compute(Coordinate coor, vector<vector<int>> &obstacleGrid) {
    stack<Coordinate> q;
    q.emplace(coor);
    while (!q.empty()) {
      Coordinate curCoor = q.top();
      int leftX = curCoor.x - 1;
      int topY = curCoor.y - 1;
      bool allComputed = true;
      int &curCoorData = buffer[curCoor.x][curCoor.y];

      // if current location has rocks, then it's path must be 0
      if (obstacleGrid[curCoor.x][curCoor.y] == 1) {
        curCoorData = 0;
        q.pop();
        continue;
      }

      // check if rely states all computed
      if (leftX >= 0 && buffer[leftX][curCoor.y] == -1) {
        allComputed = false;
        q.emplace(Coordinate{leftX, curCoor.y});
      }
      if (topY >= 0 && buffer[curCoor.x][topY] == -1) {
        allComputed = false;
        q.emplace(Coordinate{curCoor.x, topY});
      }
      if (!allComputed) {
        continue;
      }

      // now we should compute the current state
      // this if statement will be used when the matrix is 1 * 1
      if (curCoorData == -1) {
        curCoorData = 0;
      }
      if (leftX >= 0) {
        curCoorData += buffer[leftX][curCoor.y];
      }
      if (topY >= 0) {
        curCoorData += buffer[curCoor.x][topY];
      }
      q.pop();
    }
  }

public:
  // 打印二维方阵的函数
  static void printMatrix(const vector<vector<int>> &matrix, int n) {
    if (matrix.size() != n || matrix[0].size() != n) {
      cout << "Error: Matrix dimensions do not match n x n." << endl;
      return;
    }

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cout << matrix[i][j] << " ";
      }
      cout << endl;
    }
  }
  int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
    // init
    buffer.clear();
    int size = obstacleGrid.size();
    for (int i = 0; i < size; i++) {
      buffer.emplace_back(size, NON_INIT);
    }
    buffer[0][0] = 1;

    // do compute
    compute(Coordinate{size - 1, size - 1}, obstacleGrid);

    // then return
    return buffer[size - 1][size - 1];
  }
};

int main() {
  Solution s;
  vector<vector<int>> obstacleGrid;
  for (int i = 0; i < 3; i++) {
    obstacleGrid.emplace_back(3, 0);
  }
  // obstacleGrid[1][1] = 1;

  s.uniquePathsWithObstacles(obstacleGrid);
  s.printMatrix(s.buffer, 3);
}