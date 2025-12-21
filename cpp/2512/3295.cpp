#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int INF = 1e9;
const int NODE_MAX = 2003;

struct Edge {
  int to;
  int capacity;
  int rev;
};

struct Prev {
  int from;
  int edge_idx;
};

int n, m, nodes;
vector<Edge> graph[NODE_MAX];
Prev pv[NODE_MAX];
int level[NODE_MAX], index[NODE_MAX];

void add_edge(int from, int to, int capacity) {
  graph[from].push_back({ to, capacity, (int)graph[to].size() });
  graph[to].push_back({ from, 0, (int)graph[from].size() - 1 });
}

bool find_level(int source, int sink) {
  fill(level, level + nodes, -1);

  queue<int> q;
  q.push(source);
  level[source] = 0;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (int i = 0; i < (int)graph[cur].size(); i++) {
      Edge& e = graph[cur][i];

      if (e.capacity > 0 && level[e.to] == -1) {
        q.push(e.to);
        level[e.to] = level[cur] + 1;
        pv[e.to] = { cur, i };
      }
    }
  }

  return level[sink] != -1;
}

int blocking_flow(int cur, int sink, int cur_flow) {
  if (cur == sink) return cur_flow;

  for (int& i = index[cur]; i < (int)graph[cur].size(); i++) {
    Edge& e = graph[cur][i];
    
    if (e.capacity > 0 && level[e.to] == level[cur] + 1) {
      int min_flow = blocking_flow(e.to, sink, min(e.capacity, cur_flow));

      if (min_flow > 0) {
        e.capacity -= min_flow;
        graph[e.to][e.rev].capacity += min_flow;
        return min_flow;
      }
    }
  }

  return 0;
}

int max_flow(int source, int sink) {
  int total_flow = 0;

  while (find_level(source, sink)) {
    fill(index, index + nodes, 0);

    while (true) {
      int bf = blocking_flow(source, sink, INF);
      if (bf == 0) break;

      total_flow += bf;
    }
  }

  return total_flow;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tc;
  cin >> tc;

  while (tc--) {
    cin >> n >> m;
    int source = n * 2;
    int sink = n * 2 + 1;
    nodes = n * 2 + 2;

    for (int i = 0; i < n; i++) {
      add_edge(source, i, 1);
      add_edge(i + n, sink, 1);
    }

    while (m--) {
      int from, to;
      cin >> from >> to;
      add_edge(from, to + n, 1);
    }

    cout << max_flow(source, sink) << '\n';

    for (int i = 0; i < nodes; i++) graph[i].clear();
  }
}