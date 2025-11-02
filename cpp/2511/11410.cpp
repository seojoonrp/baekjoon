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
const int NODE_MAX = 52;

int n, p, nodes;
vector<Edge> graph[NODE_MAX];
int max_cost[NODE_MAX];
Prev pv[NODE_MAX];
bool in_queue[NODE_MAX];
int total_flow, total_cost;

void add_edge(int from, int to, int cost, int capacity) {
  graph[from].push_back({ to, cost, capacity, (int)graph[to].size() });
  graph[to].push_back({ from, -cost, 0, (int)graph[from].size() - 1 });
}

bool SPFA(int source, int sink) {
  fill(max_cost, max_cost + nodes, -1);
  fill(in_queue, in_queue + nodes, false);

  queue<int> q;
  q.push(source);
  max_cost[source] = 0;
  in_queue[source] = true;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    in_queue[cur] = false;

    for (int i = 0; i < (int)graph[cur].size(); i++) {
      Edge& e = graph[cur][i];

      if (e.capacity > 0 && max_cost[e.to] < max_cost[cur] + e.cost) {
        max_cost[e.to] = max_cost[cur] + e.cost;
        pv[e.to].from = cur;
        pv[e.to].edge_idx = i;

        if (!in_queue[e.to]) {
          q.push(e.to);
          in_queue[e.to] = true;
        }
      }
    }
  }

  return max_cost[sink] != -1;
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
    total_cost += cur_flow * max_cost[sink];
  }

  return total_cost;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> p;
  int source = 0;
  int sink = n + 1;
  nodes = n + 2;

  add_edge(source, 1, 0, p);
  add_edge(n, sink, 0, p);

  for (int i = 1; i < n; i++) {
    add_edge(i, i + 1, 0, INF);
  }

  int capacity[NODE_MAX][NODE_MAX] = {};
  for (int i = 1; i < n; i++) {
    for (int j = i + 1; j <= n; j++) cin >> capacity[i][j];
  }

  for (int i = 1; i < n; i++) {
    for (int j = i + 1; j <= n; j++) {
      int cost;
      cin >> cost;
      add_edge(i, j, cost, capacity[i][j]);
    }
  }

  cout << solve(source, sink) << '\n';
}