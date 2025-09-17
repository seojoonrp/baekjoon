#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
  int n;
  cin >> n;

  int board[3][1002];
  int dp[3][1002];
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < 3; ++j)
      cin >> board[j][i];
  }

  for (int i = 0; i < 3; ++i)
    dp[i][0] = board[i][0];

  for (int j = 1; j < n; ++j)
  {
    dp[0][j] = min(dp[1][j - 1], dp[2][j - 1]) + board[0][j];
    dp[1][j] = min(dp[0][j - 1], dp[2][j - 1]) + board[1][j];
    dp[2][j] = min(dp[0][j - 1], dp[1][j - 1]) + board[2][j];
  }

  // 배열로 하면 n개짜리 min 사용 가능
  int ans = min(min(dp[0][n - 1], dp[1][n - 1]), dp[2][n - 1]);
  cout << ans << endl;
}