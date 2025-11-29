#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 1002;
const int INF = 1e9 + 1;

int n, m;
int board[MAX][MAX];
int dp[MAX][MAX][3];

// 좌 하 우
int dx[3] = { 0, 1, 0 };
int dy[3] = { -1, 0, 1 };

bool is_safe(int& x, int& y) {
  if (x <= 0 || x > n) return false;
  if (y <= 0 || y > m) return false;
  return true;
}

int solve(int x, int y, int dir) {
  if (x == n && y == m) {
    return dp[x][y][dir] = board[x][y];
  }

  if (dp[x][y][dir] != -INF) {
    return dp[x][y][dir];
  }

  int& ret = dp[x][y][dir];

  for (int d = 0; d < 3; d++) {
    if (dir != 1 && d == 2 - dir) continue;

    int nx = x + dx[d];
    int ny = y + dy[d];
    if (!is_safe(nx, ny)) continue;

    ret = max(ret, solve(nx, ny, d) + board[x][y]);
  }

  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> board[i][j];
      for (int dir = 0; dir < 3; dir++) dp[i][j][dir] = -INF;
    }
  }

  int ans = max( solve(1, 1, 1), solve(1, 1, 2) );
  cout << ans << '\n';
}