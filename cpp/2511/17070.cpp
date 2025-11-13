#include <iostream>
#include <vector>
using namespace std;

const int N = 17;

int n;
bool board[N][N];
int dp[N][N][3];

bool is_safe(const int& x, const int& y) {
  if (x < 0 || x >= n) return false;
  if (y < 0 || y >= n) return false;
  return true;
}

int solve(int x, int y, char dir) {
  if (x == n - 1 && y == n - 1) return 1;

  int dir_int = dir == 'D' ? 0 : (dir == 'H' ? 1 : 2);
  if (dp[x][y][dir_int] != -1) return dp[x][y][dir_int];

  vector<char> trav;
  trav.push_back('D');
  if (dir == 'H' || dir == 'D') trav.push_back('H');
  if (dir == 'V' || dir == 'D') trav.push_back('V');

  int& ret = dp[x][y][dir_int];
  ret = 0;
  
  for (char& d : trav) {
    if (d == 'D') {
      if (is_safe(x + 1, y + 1)) {
        if (board[x][y + 1] || board[x + 1][y] || board[x + 1][y + 1]) continue;
        ret += solve(x + 1, y + 1, 'D');
      }
    } else if (d == 'H') {
      if (is_safe(x, y + 1)) {
        if (board[x][y + 1]) continue;
        ret += solve(x, y + 1, 'H');
      }
    } else if (d == 'V') {
      if (is_safe(x + 1, y)) {
        if (board[x + 1][y]) continue;
        ret += solve(x + 1, y, 'V');
      }
    }
  }

  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> board[i][j];

      for (int d = 0; d < 3; d++) dp[i][j][d] = -1;
    }
  }

  cout << solve(0, 1, 'H') << '\n';
}