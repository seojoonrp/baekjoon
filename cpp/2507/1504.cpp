#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 987654321;

struct Node {
  int index;
  int dist;

  bool operator<(const Node& other) const {
    return dist > other.dist;
  }
};

int n, e, x, y;
vector<Node> graph[802];
int dist[802];

void dijkstra(int start) {
  for (int i = 1; i <= n; ++i) dist[i] = INF;

  priority_queue<Node> pq;

  dist[start] = 0;
  pq.push({ start, 0 });

  while (!pq.empty()) {
    int cur_node = pq.top().index;
    int cur_dist = pq.top().dist;
    pq.pop();

    for (int i = 0; i < graph[cur_node].size(); ++i) {
      int next_node = graph[cur_node][i].index;
      int next_dist = cur_dist + graph[cur_node][i].dist;

      if (next_dist < dist[next_node]) {
        dist[next_node] = next_dist;
        pq.push({ next_node, next_dist });
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> e;
  while(e--) {
    int from, to, cost;
    cin >> from >> to >> cost;

    graph[from].push_back({ to, cost });
    graph[to].push_back({ from, cost });
  }

  cin >> x >> y;
  long dist_x_y = 0;
  long dist_y_x = 0;

  dijkstra(1);
  dist_x_y += dist[x];
  dist_y_x += dist[y];
  dijkstra(x);
  dist_x_y += dist[y];
  dist_y_x += dist[n];
  dijkstra(y);
  dist_x_y += dist[n];
  dist_y_x += dist[x];

  long ans = min(dist_x_y, dist_y_x);
  if (ans >= INF) cout << -1 << "\n";
  else cout << ans << "\n";
}