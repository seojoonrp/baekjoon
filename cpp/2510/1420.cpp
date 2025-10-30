#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 101;
const int NODE_MAX = 20001;
const int INF = 1e9;

struct Edge {
  int to;
  int capacity;
  int rev;
};

int n, m, OUT, nodes;
char board[MAX][MAX];
vector<Edge> graph[NODE_MAX];
int level[NODE_MAX], iter[NODE_MAX];

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

void add_edge(int from, int to, int capacity) {
  graph[from].push_back({ to, capacity, (int)graph[to].size() });
  graph[to].push_back({ from, 0, (int)graph[from].size() - 1 });
}

int coord(int& x, int& y) { return x * m + y; }

bool is_safe(int& x, int& y) {
  if (x < 0 || x >= n) return false;
  if (y < 0 || y >= m) return false;
  return true;
}

bool find_level(int source, int sink) {
  fill(level, level + nodes, -1);

  queue<int> q;
  level[source] = 0;
  q.push(source);

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (Edge& edge : graph[cur]) {
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

  for (int& i = iter[cur]; i < (int)graph[cur].size(); i++) {
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
    fill(iter, iter + nodes, 0);

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
  nodes = 2 * n * m;
  OUT = n * m;

  int source, sink;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < m; j++) {
      board[i][j] = s[j];
      if (board[i][j] == 'K') source = coord(i, j);
      if (board[i][j] == 'H') sink = coord(i, j);
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (board[i][j] != '#') {
        int capacity = 1;
        if (board[i][j] == 'K' || board[i][j] == 'H') {
          capacity = INF;
        }
        add_edge(coord(i, j), coord(i, j) + OUT, capacity);

        for (int dir = 0; dir < 4; dir++) {
          int ni = i + dx[dir];
          int nj = j + dy[dir];
          if (is_safe(ni, nj) && board[ni][nj] != '#') {
            add_edge(coord(i, j) + OUT, coord(ni, nj), INF);
          }
        }
      }
    }
  }

  int ans = max_flow(source + OUT, sink);
  if (ans >= INF) {
    cout << "-1\n";
  } else {
    cout << ans << '\n';
  }
}