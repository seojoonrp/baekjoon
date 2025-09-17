#include <iostream>
#include <algorithm>
using namespace std;

int n, k;
int w[103], v[103];
int dp[103][100003];

int main()
{
  cin >> n >> k;
  for (int i = 1; i <= n; ++i)
  {
    cin >> w[i] >> v[i];
  }

  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= k; ++j)
    {
      if (j < w[i])
        dp[i][j] = dp[i - 1][j];
      else
        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
    }
  }

  // for (int i = 1; i <= n; ++i)
  // {
  //   for (int j = 1; j <= k; ++j)
  //     cout << dp[i][j] << " ";
  //   cout << endl;
  // }

  cout << dp[n][k] << endl;
}