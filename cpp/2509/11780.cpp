#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

const int INF = 1e9;

int n, m;
int graph[101][101];
int dp[101][101];
vector<int> path[101][101];

void floyd_warshall() {
  for (int via = 1; via <= n; ++via) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (i == j) continue;
        if (dp[i][via] + dp[via][j] < dp[i][j]) {
          dp[i][j] = dp[i][via] + dp[via][j];
          path[i][j].clear();
          for (auto& x : path[i][via]) path[i][j].push_back(x);
          for (auto& x : path[via][j]) {
            if (x != via) path[i][j].push_back(x);
          }
        }
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  while (m--) {
    int from, to, cost;
    cin >> from >> to >> cost;
    if (graph[from][to] == 0) graph[from][to] = cost;
    else graph[from][to] = min(graph[from][to], cost);
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (graph[i][j]) {
        dp[i][j] = graph[i][j];
        path[i][j].push_back(i);
        path[i][j].push_back(j);
      }
      else dp[i][j] = INF;
    }
  }

  floyd_warshall();

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (dp[i][j] == INF) cout << 0 << ' ';
      else cout << dp[i][j] << ' ';
    }
    cout << '\n';
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (dp[i][j] == INF) cout << 0 << '\n';
      else {
        cout << path[i][j].size() << ' ';
        for (auto& x : path[i][j]) cout << x << ' ';
        cout << '\n';
      }
    }
  }
}