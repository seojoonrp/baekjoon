#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
  int n;
  int stair[302], dp[302];

  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> stair[i];

  dp[0] = stair[0];
  dp[1] = stair[0] + stair[1];
  dp[2] = max(stair[0] + stair[2], stair[1] + stair[2]);

  for (int i = 3; i < n; ++i)
  {
    dp[i] = max(dp[i - 2], dp[i - 3] + stair[i - 1]) + stair[i];
  }

  cout << dp[n - 1] << endl;
}