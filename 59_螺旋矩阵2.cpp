#include <iostream>
#include <vector>


using namespace std;
#define RIGHT 0
#define BUTTOM 1
#define LEFT 2
#define TOP 3
class Solution {
private:
  vector<vector<int>> initEmpty(int n) {
    vector<vector<int>> ret;
    for (int i = 0; i < n; i++) {
      ret.emplace_back(n);
    }
    return ret;
  }
  int toNextState(int n) { return ++n % 4; }

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
  vector<vector<int>> generateMatrix(int n) {
    int left = 0;
    int right = n;
    int top = 0;
    int buttom = n;

    int sum = 1;
    int state = RIGHT;
    vector<vector<int>> ret = initEmpty(n);

    while (left < right && top < buttom) {
      if (state == RIGHT) {
        for (int j = left; j < right; j++) {
          ret[top][j] = sum++;
        }
        top++;
      } else if (state == BUTTOM) {
        for (int i = top; i < buttom; i++) {
          ret[i][right - 1] = sum++;
        }
        right--;
      } else if (state == LEFT) {
        for (int j = right - 1; j >= left; j--) {
          ret[buttom - 1][j] = sum++;
        }
        buttom--;
      } else if (state == TOP) {
        for (int i = buttom - 1; i >= top; i--) {
          ret[i][left] = sum++;
        }
        left++;
      } else {
        // not possible
        exit(1);
      }
      /* code */
      state = toNextState(state);
    }
    return ret;
  }
};

int main() {
  Solution s;
  // s.generateMatrix(3);
  Solution::printMatrix(s.generateMatrix(3), 3);
}