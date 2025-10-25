#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int MAX = 300001;

int n, m;
vector<int> graph[MAX];
int tm = 1;
int d[MAX], low[MAX];
ll ans;

void dfs(int cur, int par) {
  int subgraph = 0;
  if (par != -1) subgraph = 1;

  d[cur] = tm;
  low[cur] = tm;
  tm++;

  for (int next : graph[cur]) {
    if (next == par) continue;

    if (d[next] == 0) {
      dfs(next, cur);

      low[cur] = min(low[cur], low[next]);
      if (low[next] >= d[cur]) subgraph++;
    } else {
      low[cur] = min(low[cur], d[next]);
    }
  }

  int max_tree_edges = (n - 1) - subgraph;
  if (max_tree_edges >= m - graph[cur].size()) ans += (ll)cur;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;

  for (int i = 1; i <= m; i++) {
    int n1, n2;
    cin >> n1 >> n2;
    graph[n1].push_back(n2);
    graph[n2].push_back(n1);
  }

  dfs(1, -1);

  cout << ans << '\n';
}