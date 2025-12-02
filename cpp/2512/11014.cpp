#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

typedef pair<int, int> pii;

const int N_MAX = 81;
const int NODE_MAX = 6403;
const int INF = 1e9;

struct Edge {
  int to;
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
bool visited[NODE_MAX];
char board[N_MAX][N_MAX];

pii delta[6] = {
  { -1, -1 }, { 0, -1 }, { 1, -1 },
  { -1, 1 }, { 0, 1 }, { 1, 1 }
};

int coord(int& x, int& y) { return x * m + y; }
bool is_safe(int& x, int& y) {
  if (x < 0 || x >= n) return false;
  if (y < 0 || y >= m) return false;
  return true;
}

void add_edge(int from, int to, int capacity) {
  graph[from].push_back({ to, capacity, (int)graph[to].size() });
  graph[to].push_back({ from, 0, (int)graph[from].size() - 1 });
}

bool find_augpath(int source, int sink) {
  fill(visited, visited + nodes, false);

  queue<int> q;
  q.push(source);
  visited[source] = true;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (int i = 0; i < (int)graph[cur].size(); i++) {
      Edge& e = graph[cur][i];

      if (e.capacity > 0 && !visited[e.to]) {
        q.push(e.to);
        visited[e.to] = true;
        pv[e.to] = { cur, i };
      }
    }
  }

  return visited[sink];
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

  int tc;
  cin >> tc;

  while (tc--) {
    cin >> n >> m;
    int source = n * m;
    int sink = n * m + 1;
    nodes = n * m + 2;

    int not_broken = 0;

    for (int i = 0; i < n; i++) {
      string row;
      cin >> row;
      for (int j = 0; j < m; j++) {
        board[i][j] = row[j];

        if (row[j] == '.') {
          not_broken++;

          if (j % 2 == 0) add_edge(source, coord(i, j), 1);
          else add_edge(coord(i, j), sink, 1);
        }
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j += 2) {
        for (int d = 0; d < 6; d++) {
          int ni = i + delta[d].first;
          int nj = j + delta[d].second;

          if (is_safe(ni ,nj) && board[ni][nj] == '.') {
            add_edge(coord(i, j), coord(ni, nj), 1);
          }
        }
      }
    }

    int mf = max_flow(source, sink);
    
    cout << not_broken - mf << '\n';

    for (int i = 0; i < nodes; i++) graph[i].clear();
  }
}