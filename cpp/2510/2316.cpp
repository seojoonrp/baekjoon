#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;

int n, m;
vector<int> graph[801];
int capacity[801][801];
int flow[801][801];
int parent[801];

int max_flow(int source, int sink) {
  int ans = 0;

  while (true) {
    fill(parent + 1, parent + n * 2 + 1, -1);

    queue<int> q;
    q.push(source);
    parent[source] = source;

    while (!q.empty()) {
      int cur = q.front();
      q.pop();

      for (int next : graph[cur]) {
        if (parent[next] == -1 && capacity[cur][next] - flow[cur][next] > 0) {
          q.push(next);
          parent[next] = cur;
          if (next == sink) break;
        }
      }
    }

    if (parent[sink] == -1) break;

    int min_flow = INF;
    for (int i = sink; i != source; i = parent[i]) {
      int prev = parent[i];
      min_flow = min(min_flow, capacity[prev][i] - flow[prev][i]);
    }

    for (int i = sink; i != source; i = parent[i]) {
      int prev = parent[i];
      flow[prev][i] += min_flow;
      flow[i][prev] -= min_flow;
    }

    ans += min_flow;
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  
  for (int i = 1; i <= n; i++) {
    graph[i].push_back(i + n);
    graph[i + n].push_back(i);
    capacity[i][i + n] = 1;
  }
  capacity[1][1 + n] = INF;
  capacity[2][2 + n] = INF;

  for (int i = 1; i <= m; i++) {
    int a, b;
    cin >> a >> b;
    graph[a + n].push_back(b);
    graph[b].push_back(a + n);
    capacity[a + n][b] = 1;
    graph[b + n].push_back(a);
    graph[a].push_back(b + n);
    capacity[b + n][a] = 1;
  }

  cout << max_flow(1 + n, 2) << '\n';
}