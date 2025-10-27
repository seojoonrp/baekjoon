#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;
const int MAX = 1001;

struct Node {
  int index;
  int dist;
};

struct cmp_node {
  bool operator()(const Node& n1, const Node& n2) const {
    if (n1.dist == n2.dist) return n1.index > n2.index;
    return n1.dist > n2.dist;
  }
};

int n, m;
vector<Node> graph[MAX];
int d[MAX];

void dijkstra(int start) {
  for (int i = 1; i <= n; i++) d[i] = INF;

  priority_queue<Node, vector<Node>, cmp_node> pq;
  pq.push({ start, 0 });
  d[start] = 0;

  while (!pq.empty()) {
    int cur_idx = pq.top().index;
    int cur_dist = pq.top().dist;
    pq.pop();

    if (cur_dist > d[cur_idx]) continue;

    for (Node& next : graph[cur_idx]) {
      int next_idx = next.index;
      int next_dist = next.dist;

      if (d[next_idx] > d[cur_idx] + next_dist) {
        d[next_idx] = d[cur_idx] + next_dist;
        pq.push({ next_idx, d[next_idx] });
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;

  for (int i = 1; i <= m; i++) {
    int from, to, dist;
    cin >> from >> to >> dist;
    graph[from].push_back({ to, dist });
  }

  int start, dest;
  cin >> start >> dest;
  
  dijkstra(start);

  cout << d[dest] << '\n';
}