#include <iostream>
#include <algorithm>
using namespace std;

int dp[1000002];

int main()
{
  int n;
  cin >> n;

  for (int i = 2; i <= n; ++i)
  {
    if (i % 2 == 0 && i % 3 == 0)
      dp[i] = min({dp[i / 2], dp[i / 3], dp[i - 1]}) + 1;
    else if (i % 2 == 0)
      dp[i] = min(dp[i / 2], dp[i - 1]) + 1;
    else if (i % 3 == 0)
      dp[i] = min(dp[i / 3], dp[i - 1]) + 1;
    else
      dp[i] = dp[i - 1] + 1;
  }

  // for (int i = 1; i <= n; ++i) cout << dp[i] << " ";
  // cout << endl;

  cout << dp[n] << endl;
}