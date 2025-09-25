#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;

struct Edge {
  int start, end;
  int cost;
};

int n, m, w;
vector<Edge> edges;
int dp[501];

bool bellman_ford(int start) {
  dp[start] = 0;

  for (int i = 0; i < n - 1; i++) {
    for (Edge& e : edges) {
      if (dp[e.start] != INF) dp[e.end] = min(dp[e.end], dp[e.start] + e.cost);
    }
  }

  for (Edge& e : edges) {
    if (dp[e.start] != INF) {
      if (dp[e.end] > dp[e.start] + e.cost) return true;
    }
  }
  return false;
}

int main() {
  int tc;
  scanf("%d", &tc);

  while (tc--) {
    scanf("%d %d %d", &n, &m, &w);

    while (m--) {
      int s, e, t;
      scanf("%d %d %d", &s, &e, &t);
      edges.push_back({ s, e, t });
      edges.push_back({ e, s, t });
    }
    while (w--) {
      int s, e, t;
      scanf("%d %d %d", &s, &e, &t);
      edges.push_back({ s, e, -t });
    }

    for (int i = 1; i <= n; i++) dp[i] = INF;

    bool ans = false;
    for (int i = 1; i <= n; i++) {
      if (dp[i] == INF) {
        if (bellman_ford(i)) ans = true;
      }
    }

    printf("%s\n", ans ? "YES" : "NO");

    edges.clear();
  }
}