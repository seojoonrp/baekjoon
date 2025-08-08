#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 90000000;

struct Node {
  int index;
  int dist;

  bool operator<(const Node& other) const {
    return dist > other.dist;
  }
};

int n, m, t;
vector<Node> graph[2002];

vector<int> dijkstra(int start) {
  vector<int> dist(n + 1, INF);

  priority_queue<Node> pq;

  pq.push({ start, 0 });
  dist[start] = 0;

  while (!pq.empty()) {
    Node cur = pq.top();
    pq.pop();

    for (auto& next : graph[cur.index]) {
      int next_dist = cur.dist + next.dist;
      if (next_dist < dist[next.index]) {
        pq.push({ next.index, next_dist });
        dist[next.index] = next_dist;
      }
    }
  }

  return dist;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;

  while (T--) {
    cin >> n >> m >> t;

    int s, g, h;
    cin >> s >> g >> h;

    while (m--) {
      int from, to, cost;
      cin >> from >> to >> cost;

      graph[from].push_back({ to, cost });
      graph[to].push_back({ from, cost });
    }

    vector<int> dist_s = dijkstra(s);
    vector<int> dist_g = dijkstra(g);
    vector<int> dist_h = dijkstra(h);

    vector<int> ans = {};
    while (t--) {
      int destination;
      cin >> destination;

      int dist_gh = dist_s[g] + dist_g[h] + dist_h[destination];
      int dist_hg = dist_s[h] + dist_h[g] + dist_g[destination];
      if (dist_s[destination] == dist_gh || dist_s[destination] == dist_hg) ans.push_back(destination);
    }

    sort(ans.begin(), ans.end());
    for (auto& dest : ans) cout << dest << " ";

    cout << "\n";

    for (int i = 1; i <= n; ++i) graph[i].clear();
  }
}