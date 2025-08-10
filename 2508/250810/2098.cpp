#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1e9;

int n;
int graph[17][17];
int dp[1 << 16][17]; // [visited][cur]. 이 상태에, 이 정점에서 시작점까지 순회하는데 드는 최소비용

int travel_dfs(int visited, int cur) {
  if (visited == (1 << n) - 1) {
    if (graph[cur][0] == 0) return INF;
    else return graph[cur][0];
  }

  if (dp[visited][cur] != -1) return dp[visited][cur];

  dp[visited][cur] = INF;
  for (int i = 0; i < n; ++i) {
    if (visited & (1 << i)) continue;
    if (graph[cur][i] == 0) continue;

    dp[visited][cur] = min(dp[visited][cur], graph[cur][i] + travel_dfs(visited | (1 << i), i));
  }

  return dp[visited][cur];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) cin >> graph[i][j];
  }

  for (int i = 0; i < (1 << n); ++i) {
    for (int j = 0; j < n; ++j) dp[i][j] = -1;
  }

  int ans = travel_dfs(1, 0);

  cout << ans << '\n';
}