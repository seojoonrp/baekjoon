#include <iostream>
using namespace std;

int dp[16][2];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tc;
  cin >> tc;

  while (tc--) {
    int k, n;
    cin >> k >> n;

    for (int j = 1; j <= n; j++) dp[j][0] = j;

    for (int i = 1; i <= k; i++) {
      for (int j = 1; j <= n; j++) {
        dp[j][1] = dp[j - 1][1] + dp[j][0];
      }
      for (int j = 1; j <= n; j++) {
        dp[j][0] = dp[j][1];
        dp[j][1] = 0;
      }
    }

    cout << dp[n][0] << '\n';
  }
}