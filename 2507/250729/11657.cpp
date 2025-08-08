#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const long INF = 987654321000;

struct Node {
  int index;
  long dist;
};

int n, m;
vector<Node> graph[502];
long dist[502];
bool minus_cycle = false;

void BellmanFord(int start) {
  for (int i = 1; i <= n; ++i) dist[i] = INF;

  dist[start] = 0;

  for (int cnt = 0; cnt < n - 1; ++cnt) {
    for (int i = 1; i <= n; ++i) {
      for (auto& next : graph[i]) {
        if (dist[i] != INF && dist[next.index] > dist[i] + next.dist) {
          dist[next.index] = dist[i] + next.dist;
        }
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    for (auto& next : graph[i]) {
      if (dist[i] != INF && dist[next.index] > dist[i] + next.dist) {
        minus_cycle = true;
        return;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> m;

  while (m--) {
    int from, to, cost;
    cin >> from >> to >> cost;

    graph[from].push_back({ to, cost });
  }

  BellmanFord(1);
  
  if (minus_cycle) cout << -1 << "\n";
  else {
    for (int i = 2; i <= n; ++i) cout << (dist[i] == INF ? -1 : dist[i]) << "\n";
  }
}