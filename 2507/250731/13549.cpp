#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;

struct Node {
  int index;
  int dist;

  bool operator<(const Node& other) const {
    return dist > other.dist;
  }
};

int start, dest, n;
vector<Node> graph[100002];
int dist[100002];

void dijkstra(int start) {
  for (int i = 0; i <= n; ++i) dist[i] = INF;

  priority_queue<Node> pq;

  dist[start] = 0;
  pq.push({ start, 0 });
  
  while (!pq.empty()) {
    Node cur = pq.top();
    pq.pop();

    if (dist[cur.index] < cur.dist) continue;

    for (auto& next : graph[cur.index]) {
      int nextDist = cur.dist + next.dist;
      if (dist[next.index] > nextDist) {
        dist[next.index] = nextDist;
        pq.push({ next.index, nextDist });
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> start >> dest;
  n = max(start, dest) + 1;

  for (int i = 0; i <= n; ++i) {
    if (i > 0) graph[i].push_back({ i - 1, 1 });
    if (i < n - 1) graph[i].push_back({ i + 1, 1 });
    if (i * 2 <= n) graph[i].push_back({ i * 2, 0 });
  }

  dijkstra(start);

  cout << dist[dest] << "\n";
}