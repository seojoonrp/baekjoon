#include <iostream>
#include <climits>
using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;

  int *a = new int[n];
  for (int i = 0; i < n; ++i)
    cin >> a[i];

  int *dp = new int[n]; // k번째 수로 끝나는 가장 큰 부분합
  dp[0] = a[0];
  int ans = dp[0];

  for (int i = 1; i < n; ++i)
  {
    if (dp[i - 1] + a[i] > a[i])
      dp[i] = dp[i - 1] + a[i];
    else
      dp[i] = a[i];

    ans = dp[i] > ans ? dp[i] : ans;
  }

  cout << ans << endl;

  delete[] a;
  delete[] dp;
}