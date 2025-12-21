#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int INF = 1e9;
const int MAX = 2004;

struct Edge {
  int to;
  int capacity;
  int rev;
};

struct Prev {
  int from;
  int edge_idx;
};

int n, m, k, nodes;
vector<Edge> graph[MAX];
Prev pv[MAX];

void add_edge(int from, int to, int capacity) {
  graph[from].push_back({ to, capacity, (int)graph[to].size() });
  graph[to].push_back({ from, 0, (int)graph[from].size() - 1 });
}

bool find_augpath(int source, int sink) {
  for (int i = 0; i < nodes; i++) pv[i] = { -1, -1 };

  queue<int> q;
  q.push(source);
  pv[source] = { source, -1 };

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (int i = 0; i < (int)graph[cur].size(); i++) {
      Edge& e = graph[cur][i];

      if (e.capacity > 0 && pv[e.to].from == -1) {
        q.push(e.to);
        pv[e.to] = { cur, i };
      }
    }
  }

  return pv[sink].from != -1;
}

int max_flow(int source, int sink) {
  int total_flow = 0;

  while (find_augpath(source, sink)) {
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
  }

  return total_flow;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m >> k;
  int source = 0;
  int sink = n + m + 1;
  int via = n + m + 2;
  nodes = n + m + 3;

  for (int i = 1; i <= n; i++) {
    add_edge(source, i, 1);
    add_edge(via, i, 1);
  }
  add_edge(source, via, k);
  for (int j = 1; j <= m; j++) add_edge(j + n, sink, 1);

  for (int i = 1; i <= n; i++) {
    int job_cnt;
    cin >> job_cnt;

    while (job_cnt--) {
      int job;
      cin >> job;
      add_edge(i, job + n, 1);
    }
  }

  cout << max_flow(source, sink) << '\n';
}