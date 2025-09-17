#include <iostream>
using namespace std;

const int N = 9;

int board[N][N];
int ans[N][N];

struct Point {
  int x;
  int y;
};

Point findNextZero(Point p) {
  bool ended = false;
  while (true) {
    if (p.y < N - 1) p.y++;
    else {
      p.x++;
      p.y = 0;
    }

    if (p.x == N) {
      ended = true;
      break;
    }
    if (board[p.x][p.y] == 0) break;
  }

  if (ended) {
    p.x = -1;
    p.y = -1;
  }
  return p;
}

bool isSafe(Point p, int num) {
  for (int i = 0; i < N; ++i) {
    if (board[p.x][i] == num) return false;
    if (board[i][p.y] == num) return false;
  }

  int curLUx = p.x - (p.x % 3);
  int curLUy = p.y - (p.y % 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (board[curLUx + i][curLUy + j] == num) return false;
    }
  }

  return true;
}

void sudoku(Point p) {
  Point nextP = findNextZero(p);
  if (nextP.x == -1 && nextP.y == -1) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) ans[i][j] = board[i][j];
    }
    return;
  }

  for (int i = 1; i <= 9; ++i) {
    if (isSafe(nextP, i)) {
      board[nextP.x][nextP.y] = i;
      sudoku(nextP);
      board[nextP.x][nextP.y] = 0;
    }
  }
}

int main() {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> board[i][j];
    }
  }

  Point start;
  start.x = 0;
  start.y = -1;
  sudoku(start);

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) cout << ans[i][j] << " ";
    cout << "\n";
  }
}