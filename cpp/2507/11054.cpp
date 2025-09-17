#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
  ios::sync_with_stdio(false);

  int n;
  int a[1002];

  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i];

  int inc_dp[1002];
  int dec_dp[1002];

  for (int i = 0; i < n; ++i)
  {
    inc_dp[i] = 1;
    for (int j = 0; j < i; ++j)
    {
      if (a[j] < a[i])
        inc_dp[i] = max(inc_dp[i], inc_dp[j] + 1);
    }
  }

  for (int i = n - 1; i >= 0; --i)
  {
    dec_dp[i] = 1;
    for (int j = n - 1; j > i; --j)
    {
      if (a[j] < a[i])
        dec_dp[i] = max(dec_dp[i], dec_dp[j] + 1);
    }
  }

  int ans = -1;
  for (int i = 0; i < n; ++i)
    ans = max(ans, inc_dp[i] + dec_dp[i] - 1);

  cout << ans << endl;
}