#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
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
const int NODE_MAX = 403;

int n, nodes;
vector<Edge> graph[NODE_MAX];
int min_cost[NODE_MAX];
Prev pv[NODE_MAX];
bool in_queue[NODE_MAX];
int total_flow, total_cost;

void add_edge(int from, int to, int cost, int capacity) {
  graph[from].push_back({ to, cost, capacity, (int)graph[to].size() });
  graph[to].push_back({ from, -cost, 0, (int)graph[from].size() - 1 });
}

bool SPFA(int source, int sink) {
  fill(min_cost, min_cost + nodes, INF);
  fill(in_queue, in_queue + nodes, false);

  queue<int> q;
  q.push(source);
  min_cost[source] = 0;
  in_queue[source] = true;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    in_queue[cur] = false;

    for (int i = 0; i < (int)graph[cur].size(); i++) {
      Edge& e = graph[cur][i];

      if (e.capacity > 0 && min_cost[e.to] > min_cost[cur] + e.cost) {
        min_cost[e.to] = min_cost[cur] + e.cost;
        pv[e.to].from = cur;
        pv[e.to].edge_idx = i;

        if (!in_queue[e.to]) {
          q.push(e.to);
          in_queue[e.to] = true;
        }
      }
    }
  }

  return min_cost[sink] != INF;
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
    total_cost += cur_flow * min_cost[sink];
  }

  return total_cost;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  nodes = 2 * n + 2;
  int source = 0;
  int sink = 2 * n + 1;

  for (int i = 1; i <= n; i++) {
    add_edge(source, i, 0, 1);
  }
  for (int j = 1; j <= n; j++) {
    add_edge(j + n, sink, 0, 1);
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int a_ij; cin >> a_ij;
      add_edge(i, j + n, a_ij, 1);
    }
  }

  cout << solve(source, sink) << '\n';
}