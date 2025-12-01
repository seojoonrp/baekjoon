#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int NODE_MAX = 1003;
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

int n, k, nodes;
vector<Edge> graph[NODE_MAX];
Prev pv[NODE_MAX];
bool visited[NODE_MAX];

void add_edge(int from, int to, int capacity) {
  graph[from].push_back({ to, capacity, (int)graph[to].size() });
  graph[to].push_back({ from, 0, (int)graph[to].size() - 1 });
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

  cin >> n >> k;
  int source = 0;
  int sink = 2 * n + 1;
  nodes = 2 * n + 2;

  for (int i = 1; i <= n; i++) {
    add_edge(source, i, 1);
    add_edge(i + n, sink, 1);
  }

  for (int i = 1; i <= k; i++) {
    int row, col;
    cin >> row >> col;
    add_edge(row, col + n, INF);
  }

  int mf = max_flow(source, sink);
  cout << mf << '\n';
}