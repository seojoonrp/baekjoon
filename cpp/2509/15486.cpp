#include <iostream>
#include <algorithm>
using namespace std;

int n;
int t[1500002];
int value[1500002];
int dp[1500002];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> t[i] >> value[i];

  for (int i = 1; i <= n; ++i) {
    dp[i] = max(dp[i], dp[i - 1]);
    if (i + t[i] <= n + 1) {
      dp[i + t[i]] = max(dp[i + t[i]], dp[i] + value[i]);
    }
  }

  cout << max(dp[n], dp[n + 1]) << '\n';
}