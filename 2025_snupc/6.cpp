#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
using ll = long long;

int n;
int score[100001];
int dp[100001][101];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> score[i];

  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= 100; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (j == score[i]) dp[i][j] = i;
      if (j >= score[i] && dp[i - 1][j - score[i]] > 0) {
        dp[i][j] = max(dp[i][j], dp[i - 1][j - score[i]]);
      }
    }
  }

  ll ans = 0;
  for (int i = 1; i <= n; ++i) {
    // for (int j = 0; j <= 100; ++j) {
    //   if (dp[i][j] != 0) {
    //     cout << i << ' ' << j << ' ' << dp[i][j] << '\n';
    //   }
    // }
    ans += dp[i][100];
  }
  cout << ans << '\n';
}