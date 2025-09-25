#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

const ll MINF = -1e18;

struct Edge {
  int start, end;
  ll value;
};

int n, s, e, m;
vector<Edge> edges;
ll value[51];
ll dp[51];
vector<int> graph[51];
bool visited[51];

bool has_path(int node, int target) {
  visited[node] = true;
  if (node == target) return true;

  bool ret = false;
  for (int& next : graph[node]) {
    if (!visited[next] && has_path(next, target)) ret = true;
  }

  return ret;
}

bool bellman_ford(int start) {
  dp[start] = value[start];

  for (int i = 0; i < n - 1; i++) {
    for (Edge& edge : edges) {
      if (dp[edge.start] != MINF) {
        dp[edge.end] = max(dp[edge.start] + edge.value, dp[edge.end]);
      }
    }
  }

  for (Edge& edge : edges) {
    if (dp[edge.start] != MINF) {
      if (dp[edge.start] + edge.value > dp[edge.end]) {
        fill(visited, visited + n, false);
        if (has_path(edge.end, e)) return true;
      }
    }
  }
  return false;
}

int main() {
  scanf("%d %d %d %d", &n, &s, &e, &m);

  vector<Edge> temp_edges;
  for (int i = 0; i < m; i++) {
    int s, e;
    ll cost;
    scanf("%d %d %lld", &s, &e, &cost);
    temp_edges.push_back({ s, e, cost });
  }

  for (int i = 0; i < n; i++) {
    scanf("%lld", &value[i]);
    dp[i] = MINF;
  }

  for (Edge& edge : temp_edges) {
    graph[edge.start].push_back(edge.end);
    edges.push_back({ edge.start, edge.end, value[edge.end] - edge.value });
  }

  bool has_cycle = bellman_ford(s);
  if (dp[e] == MINF) printf("gg\n");
  else if (has_cycle) printf("Gee\n");
  else printf("%lld\n", dp[e]);
}