#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int MAX = 2004;
// source = 0, sink = n + 1, bridge = n + 2

int n, m, k;
vector<int> graph[MAX];
int capacity[MAX][MAX];
int flow[MAX][MAX];
int parent[MAX];
int source, sink, bridge, nodes;

int max_flow() {
  int ans = 0;

  while (true) {
    fill(parent, parent + nodes, -1);

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

void make_graph() {
  for (int i = 1; i <= n; i++) {
    int work_count;
    cin >> work_count;
    while (work_count--) {
      int x;
      cin >> x;
      graph[i].push_back(x + n);
      graph[x + n].push_back(i);
      capacity[i][x + n] = 1;
    }
  }

  for (int i = 1; i <= n; i++) {
    graph[source].push_back(i);
    graph[i].push_back(source);
    capacity[source][i] = 1;
    graph[bridge].push_back(i);
    graph[i].push_back(bridge);
    capacity[bridge][i] = k;
  }
  for (int i = n + 1; i <= n + m; i++) {
    graph[i].push_back(sink);
    graph[sink].push_back(i);
    capacity[i][sink] = 1;
  }
  graph[source].push_back(bridge);
  graph[bridge].push_back(source);
  capacity[source][bridge] = k;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m >> k;
  source = 0;
  sink = n + m + 1;
  bridge = n + m + 2;
  nodes = n + m + 3;

  make_graph();

  cout << max_flow() << '\n';
}