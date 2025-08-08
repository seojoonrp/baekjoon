#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
  int n;
  int board[502][502];
  int dp[502];

  cin >> n;
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j <= i; ++j)
      cin >> board[i][j];
  }

  dp[0] = board[0][0];
  for (int i = 1; i < n; ++i)
  {
    for (int j = i; j >= 0; --j)
    {
      if (j == i)
      {
        dp[j] = dp[j - 1] + board[i][j];
      }
      else if (j == 0)
      {
        dp[j] = dp[j] + board[i][j];
      }
      else
      {
        dp[j] = max(dp[j], dp[j - 1]) + board[i][j];
      }
    }
  }

  int ans = *max_element(dp, dp + n);
  cout << ans << endl;
}