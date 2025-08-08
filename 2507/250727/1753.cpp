#include <iostream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

int INF = 987654321;

struct Node {
  int node;
  int dist;

  bool operator<(const Node& other) const {
    return dist > other.dist;
  }
};

int v, e, k;
vector<Node> graph[20002];
int dist[20002];

void dijkstra(int start) {
  priority_queue<Node> pq;

  dist[start] = 0;
  pq.push({ start, 0 });

  while (!pq.empty()) {
    int cur_node = pq.top().node;
    int cur_dist = pq.top().dist;
    pq.pop();

    for (int i = 0; i < graph[cur_node].size(); ++i) {
      int next_node = graph[cur_node][i].node;
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

  cin >> v >> e >> k;
  while (e--) {
    int from, to, cost;
    cin >> from >> to >> cost;

    graph[from].push_back({ to, cost });
  }

  for (int i = 1; i <= v; ++i) dist[i] = INF;

  dijkstra(k);

  for (int i = 1; i <= v; ++i) {
    if (dist[i] == INF) cout << "INF" << "\n";
    else cout << dist[i] << "\n";
  }
}