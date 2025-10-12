#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int N_MAX = 51;
const int NODE_MAX = 103;
const int INF = 1e9;

struct Edge {
  int to;
  int capacity;
  int rev;
};

int n, total_sum;
int row_sum[N_MAX], col_sum[N_MAX];
vector<Edge> graph[NODE_MAX];
int level[NODE_MAX], iter[NODE_MAX];

void add_edge(int from, int to, int capacity) {
  graph[from].push_back({ to, capacity, (int)graph[to].size() });
  graph[to].push_back({ from, 0, (int)graph[from].size() - 1 });
}

void make_graph(int x, int source, int sink) {
  graph[source].clear();
  graph[sink].clear();
  for (int i = 0; i < n; i++) {
    graph[i].clear();
    graph[i + n].clear();
  }

  for (int i = 0; i < n; i++) {
    add_edge(source, i, row_sum[i]);
    add_edge(i + n, sink, col_sum[i]);
    for (int j = 0; j < n; j++) {
      add_edge(i, j + n, x);
    }
  }
}

bool find_level(int source, int sink) {
  fill(level, level + sink + 1, -1);

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

bool check(int x, int source, int sink) {
  make_graph(x, source, sink);

  int total_flow = 0;

  while (find_level(source, sink)) {
    fill(iter, iter + sink + 1, 0);

    int bf;
    while ((bf = blocking_flow(source, sink, INF)) > 0) {
      total_flow += bf;
    }
  }

  return total_flow == total_sum;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  int source = 2 * n;
  int sink = 2 * n + 1;

  int max_sum = -1;
  for (int i = 0; i < n; i++) {
    cin >> row_sum[i];
    max_sum = max(max_sum, row_sum[i]);
    total_sum += row_sum[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> col_sum[i];
    max_sum = max(max_sum, col_sum[i]);
  }

  int lo = 0;
  int hi = max_sum;

  while (lo < hi) {
    int mid = (lo + hi) / 2;
    bool consistent = check(mid, source, sink);

    if (consistent) hi = mid;
    else lo = mid + 1;
  }

  cout << hi << '\n';
  check(hi, source, sink);

  int ans[N_MAX][N_MAX];
  for (int i = 0; i < n; i++) {
    for (Edge& edge : graph[i]) {
      if (edge.to >= n && edge.to < 2 * n) ans[i][edge.to - n] = hi - edge.capacity;
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cout << ans[i][j] << ' ';
    cout << '\n';
  }
}