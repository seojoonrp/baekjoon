#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int N_MAX = 51;
const int MAX = 5003;

struct Edge {
  int to;
  int capacity;
  int rev;
};

int n, m;
int grid[N_MAX][N_MAX];
vector<Edge> graph[MAX];
int level[MAX], iter[MAX];

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

void add_edge(int from, int to, int capacity) {
  graph[from].push_back({ to, capacity, (int)graph[to].size() });
  graph[to].push_back({ from, 0, (int)graph[from].size() - 1 });
}

int coord(const int& i, const int& j) { return i * m + j; }

bool is_safe(const int& i, const int& j) {
  if (i < 0 || i >= n) return false;
  if (j < 0 || j >= m) return false;
  return true;
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

int maximum_flow(int source, int sink) {
  int total_flow = 0;

  while (find_level(source, sink)) {
    fill(iter, iter + sink + 1, 0);

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

  int tc;
  cin >> tc;

  while (tc--) {
    cin >> n >> m;

    int source = n * m;
    int sink = n * m + 1;

    int total_sum = 0;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> grid[i][j];
        total_sum += grid[i][j];

        if ((i + j) % 2 == 0) {
          add_edge(source, coord(i, j), grid[i][j]);

          for (int dir = 0; dir < 4; dir++) {
            int ni = i + dx[dir];
            int nj = j + dy[dir];
            if (is_safe(ni, nj)) add_edge(coord(i, j), coord(ni, nj), INF);
          }
        } else {
          add_edge(coord(i, j), sink, grid[i][j]);
        }
      }
    }
    
    cout << total_sum - maximum_flow(source, sink) << '\n';

    for (int i = 0; i <= sink; i++) graph[i].clear();
  }
}