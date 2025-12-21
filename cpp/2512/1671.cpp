#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int INF = 1e9;
const int N_MAX = 51;
const int NODE_MAX = 103;

struct Edge {
  int to;
  int capacity;
  int rev;
};

struct Prev {
  int from;
  int edge_idx;
};

struct Shark {
  int size;
  int speed;
  int intel;

  bool operator==(const Shark& other) const {
    return size == other.size && speed == other.speed && intel == other.intel;
  }

  bool operator>=(const Shark& other) const {
    return size >= other.size && speed >= other.speed && intel >= other.intel;
  }
};

int n, nodes;
vector<Edge> graph[NODE_MAX];
Prev pv[NODE_MAX];
Shark sharks[N_MAX];

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

  cin >> n;
  int source = 0;
  int sink = n * 2 + 1;
  nodes = n * 2 + 2;

  for (int i = 1; i <= n; i++) {
    add_edge(source, i, 2);
    add_edge(i + n, sink, 1);
  }

  for (int i = 1; i <= n; i++) {
    cin >> sharks[i].size >> sharks[i].speed >> sharks[i].intel;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (sharks[i] == sharks[j]) {
        add_edge(i, j + n, 1);
      } else {
        if (sharks[i] >= sharks[j]) add_edge(i, j + n, 1);
        if (sharks[j] >= sharks[i]) add_edge(j, i + n, 1);
      }
    }
  }

  cout << n - max_flow(source, sink) << '\n';
}