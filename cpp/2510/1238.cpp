#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;

struct Node {
  int index, dist;

  bool operator>(const Node& other) const {
    return dist > other.dist;
  }
};

int n, m;
vector<Node> graph[1001], graph_t[1001];
int dist[1001], dist_t[1001];

void dijkstra(int start, vector<Node> graph[], int dist[]) {
  priority_queue<Node, vector<Node>, greater<Node>> pq;

  fill(dist + 1, dist + n + 1, INF);
  dist[start] = 0;
  pq.push({ start, 0 });

  while (!pq.empty()) {
    Node cur = pq.top();
    pq.pop();

    if (cur.dist > dist[cur.index]) continue;

    for (Node& next : graph[cur.index]) {
      if (dist[next.index] > cur.dist + next.dist) {
        dist[next.index] = cur.dist + next.dist;
        pq.push({ next.index, dist[next.index] });
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int house;
  cin >> n >> m >> house;

  for (int i = 1; i <= m; i++) {
    int from, to, d;
    cin >> from >> to >> d;
    graph[from].push_back({ to, d });
    graph_t[to].push_back({ from, d });
  }

  dijkstra(house, graph, dist);
  dijkstra(house, graph_t, dist_t);

  int ans = -1;
  for (int i = 1; i <= n; i++) {
    ans = max(ans, dist[i] + dist_t[i]);
  }

  cout << ans << '\n';
}