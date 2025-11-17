#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int NODE_MAX = 2003;

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

int n, m, nodes;
vector<Edge> graph[NODE_MAX];
Prev pv[NODE_MAX];
int min_cost[NODE_MAX];
bool in_queue[NODE_MAX];

void add_edge(int from, int to, int cost, int capacity) {
  graph[from].push_back({ to, cost, capacity, (int)graph[to].size() });
  graph[to].push_back({ from, -cost, 0, (int)graph[from].size() - 1 });
}

bool SPFA(int source, int sink) {
  fill(min_cost, min_cost + nodes, INF);
  fill(in_queue, in_queue + nodes, false);

  queue<int> q;
  min_cost[source] = 0;
  q.push(source);
  in_queue[source] = true;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    in_queue[cur] = false;

    for (int i = 0; i < (int)graph[cur].size(); i++) {
      Edge& e = graph[cur][i];

      if (e.capacity > 0 && min_cost[e.to] > min_cost[cur] + e.cost) {
        min_cost[e.to] = min_cost[cur] + e.cost;
        pv[e.to] = { cur, i };

        if (!in_queue[e.to]) {
          q.push(e.to);
          in_queue[e.to] = true;
        }
      }
    }
  }

  return min_cost[sink] != INF;
}

// { max flow, min cost }
pair<int, int> MCMF(int source, int sink) {
  int total_flow = 0, total_cost = 0;

  while (SPFA(source, sink)) {
    int cur_flow = INF;
    for (int i = sink; i != source; i = pv[i].from) {
      Edge& e = graph[pv[i].from][pv[i].edge_idx];
      cur_flow = min(cur_flow, e.capacity);
    }

    for (int i = sink; i != source; i = pv[i].from) {
      Edge& e = graph[pv[i].from][pv[i].edge_idx];
      e.capacity -= cur_flow;
      graph[i][e.rev].capacity += cur_flow;
    }

    total_flow += cur_flow;
    total_cost += cur_flow * min_cost[sink];
  }

  return { total_flow, total_cost };
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  while (cin >> n >> m) {
    int source = 0;
    int sink = 2 * n + 1;
    nodes = 2 * n + 2;

    add_edge(source, 1 + n, 0, 2);
    add_edge(n, sink, 0, 2);

    for (int i = 2; i < n; i++) {
      add_edge(i, i + n, 0, 1);
    }
  
    for (int i = 1; i <= m; i++) {
      int from, to, cost;
      cin >> from >> to >> cost;
      add_edge(from + n, to, cost, 1);
    }
  
    pair<int, int> ans = MCMF(source, sink);
    cout << ans.second << '\n';

    for (int i = 0; i < nodes; i++) graph[i].clear();
  }
}