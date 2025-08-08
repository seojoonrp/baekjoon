#include <iostream>
using namespace std;

int n, ans;
bool** board;

bool isSafe(int r, int c) {
  for (int i = 0; i < r; ++i) {
    if (board[i][c]) return false;
  }
  for (int i = 1; r - i >= 0 && c - i >= 0; ++i) {
    if (board[r - i][c - i]) return false;
  }
  for (int i = 1; r - i >= 0 && c + i < n; ++i) {
    if (board[r - i][c + i]) return false;
  }

  return true;
}

void nQueen(int r) {
  if (r == n) {
    ans++;
    return;
  }

  for (int i = 0; i < n; ++i) {
    if (isSafe(r, i)) {
      board[r][i] = true;
      nQueen(r + 1);
      board[r][i] = false;
    }
  }
}

int main() {
  cin >> n;
  ans = 0;

  board = new bool*[n];

  for (int i = 0; i < n; ++i) {
    board[i] = new bool[n];
    for (int j = 0; j < n; ++j) {
      board[i][j] = false;
    }
  }

  nQueen(0);
  cout << ans << endl;

  for (int i = 0; i < n; ++i) {
    delete[] board[i];
  }
  delete[] board;
}