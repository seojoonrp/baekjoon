#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
  int n;
  int a[10002];

  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i];

  int dp[10002];
  dp[0] = a[0];
  dp[1] = a[0] + a[1];
  dp[2] = max({dp[1], a[0] + a[2], a[1] + a[2]});

  for (int i = 3; i < n; ++i)
  {
    dp[i] = max({dp[i - 1],
                 dp[i - 2] + a[i],
                 dp[i - 3] + a[i - 1] + a[i]});
  }

  cout << dp[n - 1] << endl;
}