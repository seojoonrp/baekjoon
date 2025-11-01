#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Edge {
  int to;
  int cost;
  int capacity;
  int rev;
};

struct Prev {
  int from;
  int edge_idx;
};

const int INF = 1e9;
const int NODE_MAX = 503;

int n, m, nodes;
vector<Edge> graph[NODE_MAX];
int min_dist[NODE_MAX];
Prev pv[NODE_MAX];
bool in_queue[NODE_MAX];
int total_flow, total_cost;

void add_edge(int from, int to, int cost, int capacity) {
  graph[from].push_back({ to, cost, capacity, (int)graph[to].size() });
  graph[to].push_back({ from, -cost, 0, (int)graph[from].size() - 1 });
}

bool SPFA(int source, int sink) {
  fill(min_dist, min_dist + nodes, INF);
  fill(in_queue, in_queue + nodes, false);

  queue<int> q;
  q.push(source);
  min_dist[source] = 0;
  in_queue[source] = true;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    in_queue[cur] = false;

    for (int i = 0; i < (int)graph[cur].size(); i++) {
      Edge& e = graph[cur][i];

      if (e.capacity > 0 && min_dist[e.to] > min_dist[cur] + e.cost) {
        min_dist[e.to] = min_dist[cur] + e.cost;
        pv[e.to].from = cur;
        pv[e.to].edge_idx = i;

        if (!in_queue[e.to]) {
          q.push(e.to);
          in_queue[e.to] = true;
        }
      }
    }
  }

  return min_dist[sink] != INF;
}

int solve(int source, int sink) {
  while (SPFA(source, sink)) {
    int cur_flow = INF;

    for (int i = sink; i != source; i = pv[i].from) {
      Prev p = pv[i];

      cur_flow = min(cur_flow, graph[p.from][p.edge_idx].capacity);
    }

    for (int i = sink; i != source; i = pv[i].from) {
      Prev p = pv[i];

      graph[p.from][p.edge_idx].capacity -= cur_flow;
      graph[i][graph[p.from][p.edge_idx].rev].capacity += cur_flow;
    }

    total_flow += cur_flow;
    total_cost += cur_flow * min_dist[sink];
  }

  return total_cost;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tc;
  cin >> tc;

  while (tc--) {
    cin >> n >> m;
    int source = 0;
    int sink = n + 1;
    nodes = n + 2;

    for (int i = 1; i <= m; i++) {
      int n1, n2;
      cin >> n1 >> n2;
      add_edge(n1, n2, 1, INF);
      add_edge(n2, n1, 1, INF);
    }

    for (int i = 1; i <= n; i++) {
      int black;
      cin >> black;
      if (black == 1) add_edge(source, i, 0, 1);
    }

    for (int i = 1; i <= n; i++) {
      int black;
      cin >> black;
      if (black == 1) add_edge(i, sink, 0, 1);
    }

    cout << solve(source, sink) << '\n';

    total_flow = 0;
    total_cost = 0;
    for (int i = 0; i < nodes; i++) {
      graph[i].clear();
    }
  }
}