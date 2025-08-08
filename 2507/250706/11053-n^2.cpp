#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
  int n;
  int a[1002];
  int dp[1002];

  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i];

  dp[0] = 1;
  int ans = dp[0];

  for (int i = 1; i < n; ++i)
  {
    dp[i] = 1;

    for (int j = 0; j < i; ++j)
    {
      if (a[j] < a[i])
        dp[i] = max(dp[j] + 1, dp[i]);
    }

    ans = max(ans, dp[i]);
  }

  cout << ans << endl;
}