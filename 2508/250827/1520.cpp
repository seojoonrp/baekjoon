#include <iostream>
using namespace std;

int n, m;
int board[502][502];
int dp[502][502];

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

bool isSafe(int x, int y) {
  if (x < 0 || x >= n) return false;
  if (y < 0 || y >= m) return false;
  return true;
}

int dfs(int x, int y) {
  if (x == n - 1 && y == m - 1) return dp[n - 1][m - 1] = 1;

  if (dp[x][y] != -1) return dp[x][y];

  int cur = board[x][y];
  int ans = 0;

  for (int dir = 0; dir < 4; ++dir) {
    int nx = x + dx[dir];
    int ny = y + dy[dir];

    if (isSafe(nx, ny) && board[nx][ny] < cur) {
      ans += dfs(nx, ny);
    }
  }

  return dp[x][y] = ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> board[i][j];
      dp[i][j] = -1;
    }
  }

  cout << dfs(0, 0) << '\n';
}