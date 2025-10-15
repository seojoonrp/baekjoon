#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int MAX = 803;

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
vector<Edge> graph[MAX];
int min_dist[MAX];
Prev pre[MAX];
bool in_queue[MAX];
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

      if (e.capacity > 0 && min_dist[cur] + e.cost < min_dist[e.to]) {
        min_dist[e.to] =  min_dist[cur] + e.cost;
        pre[e.to].from = cur;
        pre[e.to].edge_idx = i;
        
        if (!in_queue[e.to]) {
          q.push(e.to);
          in_queue[e.to] = true;
        }
      }
    }
  }

  return min_dist[sink] != INF;
}

void solve(int source, int sink) {
  while (SPFA(source, sink)) {
    int cur_flow = INF;

    for (int i = sink; i != source; i = pre[i].from) {
      Prev p = pre[i];
      cur_flow = min(cur_flow, graph[p.from][p.edge_idx].capacity);
    }

    for (int i = sink; i != source; i = pre[i].from) {
      Prev p = pre[i];

      graph[p.from][p.edge_idx].capacity -= cur_flow;
      graph[i][graph[p.from][p.edge_idx].rev].capacity += cur_flow;
    }

    total_flow += cur_flow;
    total_cost += cur_flow * min_dist[sink];
  }

  cout << total_flow << '\n' << total_cost << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  int source = 0;
  int sink = n + m + 1;
  nodes = n + m + 2;

  for (int i = 1; i <= n; i++) {
    int job_count;
    cin >> job_count;

    for (int j = 1; j <= job_count; j++) {
      int job, cost;
      cin >> job >> cost;

      add_edge(i, job + n, cost, 1);
    }
  }

  for (int i = 1; i <= n; i++) {
    add_edge(source, i, 0, 1);
  }
  for (int i = 1; i <= m; i++) {
    add_edge(i + n, sink, 0, 1);
  }

  solve(source, sink);
}