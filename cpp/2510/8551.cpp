#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 10001;
const int INF = 1e9;

struct Edge {
  int to;
  int capacity;
  int rev;
};

int n, m;
vector<Edge> graph[MAX];
int level[MAX];
int iter[MAX];

void add_edge(int from, int to, int capacity) {
  graph[from].push_back({ to, capacity, (int)graph[to].size() });
  graph[to].push_back({ from, 0, (int)graph[from].size() - 1 });
}

bool find_level(int source, int sink) {
  fill(level + 1, level + n + 1, -1);

  queue<int> q;
  level[source] = 0;
  q.push(source);

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (const auto& edge : graph[cur]) {
      if (edge.capacity > 0 && level[edge.to] == -1) {
        level[edge.to] = level[cur] + 1;
        q.push(edge.to);
      }
    }
  }

  return level[sink] != -1;
}

int blocking_flow(int cur, int sink, int cur_bf) {
  if (cur == sink) return cur_bf;

  for (int& i = iter[cur]; i < graph[cur].size(); i++) {
    Edge& edge = graph[cur][i];

    if (edge.capacity > 0 && level[edge.to] == level[cur] + 1) {
      int next_bf = blocking_flow(edge.to, sink, min(cur_bf, edge.capacity));

      if (next_bf > 0) {
        edge.capacity -= next_bf;
        graph[edge.to][edge.rev].capacity += next_bf;
        return next_bf;
      }
    }
  }

  return 0;
}

int max_flow(int source, int sink) {
  int total_flow = 0;

  while (find_level(source, sink)) {
    fill(iter + 1, iter + n + 1, 0);

    int bf;
    while ((bf = blocking_flow(source, sink, INF)) > 0) {
      total_flow += bf;
    }
  }

  return total_flow;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  int source = 1;
  int sink = n;

  while (m--) {
    int from, to;
    cin >> from >> to;
    add_edge(from, to, 1);
  }

  cout << max_flow(source, sink) << '\n';
}