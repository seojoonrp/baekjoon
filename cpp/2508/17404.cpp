#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1e9;

int n;
int board[1002][3];
int dp[1002][3][3];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> board[i][0] >> board[i][1] >> board[i][2];

    for (int j = 0; j < 3; ++j) {
      for (int k = 0; k < 3; ++k) dp[i][j][k] = INF;
    }
  }

  for (int i = 0; i < 3; ++i) dp[0][i][i] = board[0][i];

  for (int i = 1; i < n; ++i) {
    for (int k = 0; k < 3; ++k) {
      dp[i][0][k] = min(dp[i - 1][1][k], dp[i - 1][2][k]) + board[i][0];
      dp[i][1][k] = min(dp[i - 1][0][k], dp[i - 1][2][k]) + board[i][1];
      dp[i][2][k] = min(dp[i - 1][0][k], dp[i - 1][1][k]) + board[i][2];
    }
  }

  int ans = INF;
  for (int j = 0; j < 3; ++j) {
    for (int k = 0; k < 3; ++k) {
      if (k != j) ans = min(ans, dp[n - 1][j][k]);
    }
  }

  cout << ans << '\n';
}