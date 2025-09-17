#include <iostream>
#include <algorithm>
using namespace std;

int n, m, total_cost;
int value[102];
int cost[102];
int dp[102][10002]; // dp[i][j] : i번째 앱까지 고려했을 때 j 이하의 비용을 소모해서 얻을 수 있는 최대 메모리

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> m;
  for (int i = 1; i <= n; ++i) cin >> value[i];
  for (int i = 1; i <= n; ++i) {
    cin >> cost[i];
    total_cost += cost[i];
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= total_cost; ++j) {
      if (j < cost[i]) dp[i][j] = dp[i - 1][j];
      else dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - cost[i]] + value[i]);
    }
  }

  for (int j = 0; j <= total_cost; ++j) {
    if (dp[n][j] >= m) {
      cout << j << '\n';
      break;
    }
  }
}