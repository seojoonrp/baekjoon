#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int n, m, goal;
int cost[1002], indegree[1002], dp[1002];
vector<int> graph[1002];
queue<int> q;

int main() {
  int T;
  cin >> T;

  while (T--) {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> cost[i];
    while (m--) {
      int from, to;
      cin >> from >> to;
      graph[from].push_back(to);
      indegree[to]++;
    }
    cin >> goal;

    for (int i = 1; i <= n; ++i) {
      if (indegree[i] == 0) {
        q.push(i);
        dp[i] = cost[i];
      }
    }

    while (!q.empty()) {
      int cur = q.front();
      q.pop();

      for (auto& next : graph[cur]) {
        indegree[next]--;
        if (indegree[next] == 0) q.push(next);

        dp[next] = max(dp[next], dp[cur] + cost[next]);
      }
    }

    cout << dp[goal] << '\n';

    for (int i = 1; i <= n; ++i) {
      graph[i].clear();
      dp[i] = indegree[i] = cost[i] = 0;
    }
  }
}