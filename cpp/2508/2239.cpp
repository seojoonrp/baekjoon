#include <iostream>
#include <string>
using namespace std;

const int n = 9;
int board[n][n];
bool found_ans = false;

bool is_safe(int x, int y, int num) {
  for (int i = 0; i < n; ++i) {
    if (i != y && board[x][i] == num) return false;
    if (i != x && board[i][y] == num) return false;
  }

  int pivot_x = x - x % 3;
  int pivot_y = y - y % 3;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (board[pivot_x + i][pivot_y + j] == num) return false;
    }
  }

  return true;
}

void sudoku(int x, int y) {
  if (found_ans) return;

  if (x == n - 1 && y == n) {
    found_ans = true;

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) cout << board[i][j];
      cout << "\n";
    }

    return;
  }

  if (y == n) {
    y = 0;
    x++;
  }

  if (board[x][y] != 0) sudoku(x, y + 1);
  else {
    for (int next = 1; next <= 9; ++next) {
      if (is_safe(x, y, next)) {
        board[x][y] = next;
        sudoku(x, y + 1);
        if (found_ans) return;
        board[x][y] = 0;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < n; ++j) board[i][j] = s[j] - '0';
  }

  sudoku(0, 0);
}