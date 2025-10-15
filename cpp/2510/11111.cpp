#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

const int N_MAX = 51;
const int MAX = 5003;
const int INF = 1e9;

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

int tofu_cost[5][5] = {
  { 10, 8, 7, 5, 1 },
  { 8, 6, 4, 3, 1 },
  { 7, 4, 3, 2, 1 },
  { 5, 3, 2, 2, 1 },
  { 1, 1, 1, 1, 0 }
};

int n, m, nodes;
vector<Edge> graph[MAX];
int tofu_map[N_MAX][N_MAX];
int max_dist[MAX];
Prev pre[MAX];
bool in_queue[MAX];

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

bool is_safe(int& x, int& y) {
  if (x < 0 || x >= n) return false;
  if (y < 0 || y >= m) return false;
  return true;
}

int coord(int& x, int& y) { return x * m + y; }

void add_edge(int from, int to, int cost, int capacity) {
  graph[from].push_back({ to, cost, capacity, (int)graph[to].size() });
  graph[to].push_back({ from, -cost, 0, (int)graph[from].size() - 1 });
}

bool SPFA(int source, int sink) {
  fill(max_dist, max_dist + nodes, -INF);
  fill(in_queue, in_queue + nodes, false);

  queue<int> q;
  q.push(source);
  max_dist[source] = 0;
  in_queue[source] = true;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    in_queue[cur] = false;

    for (int i = 0; i < (int)graph[cur].size(); i++) {
      Edge& e = graph[cur][i];

      if (e.capacity > 0 && max_dist[cur] + e.cost > max_dist[e.to]) {
        max_dist[e.to] = max_dist[cur] + e.cost;
        pre[e.to].from = cur;
        pre[e.to].edge_idx = i;
        
        if (!in_queue[e.to]) {
          q.push(e.to);
          in_queue[e.to] = true;
        }
      }
    }
  }

  return max_dist[sink] != -INF;
}

void solve(int source, int sink) {
  int total_flow = 0;
  int total_cost = 0;

  while (SPFA(source, sink) && max_dist[sink] > 0) {
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
    total_cost += cur_flow * max_dist[sink];
  }

  cout << total_cost << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  int source = n * m;
  int sink = n * m + 1;
  nodes = n * m + 2;

  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < m; j++) tofu_map[i][j] = s[j] - 'A' - (int)(s[j] == 'F');
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if ((i + j) % 2 == 0) {
        add_edge(source, coord(i, j), 0, 1);

        for (int dir = 0; dir < 4; dir++) {
          int ni = i + dx[dir];
          int nj = j + dy[dir];
          if (is_safe(ni, nj)) {
            add_edge(coord(i, j), coord(ni, nj), tofu_cost[tofu_map[i][j]][tofu_map[ni][nj]], 1);
          }
        }
      } else {
        add_edge(coord(i, j), sink, 0, 1);
      }
    }
  }

  solve(source, sink);
}