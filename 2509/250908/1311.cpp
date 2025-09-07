#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int INF = 1e9;

int n;
int cost[21][21];
int dp[1 << 20];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) cin >> cost[i][j];
  }

  for (int i = 1; i < (1 << n); ++i) dp[i] = INF;

  for (int mask = 0; mask < (1 << n); ++mask) {
    if (dp[mask] == INF) continue; // 굳이 필요없긴함

    int cnt = __builtin_popcount(mask);

    for (int i = 0; i < n; ++i) {
      if (mask & (1 << i)) continue;

      int next_mask = mask | (1 << i);
      dp[next_mask] = min(dp[next_mask], dp[mask] + cost[i][cnt]);
    }
  }

  cout << dp[(1 << n) - 1] << '\n';
}