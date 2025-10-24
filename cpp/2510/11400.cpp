#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 100001;

int n, m;
vector<int> graph[MAX];
int d[MAX], parent[MAX], low[MAX];
vector<pair<int, int>> ans;

void dfs(int cur, int& tm) {
  d[cur] = tm;
  low[cur] = tm;
  tm++;

  for (int next : graph[cur]) {
    if (parent[cur] == next) continue;

    if (d[next] == 0) {
      parent[next] = cur;
      dfs(next, tm);

      if (d[cur] < low[next]) ans.push_back({ cur, next });

      low[cur] = min(low[cur], low[next]);
    } else {
      low[cur] = min(low[cur], d[next]);
    }
  }
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

  for (int i = 1; i <= n; i++) {
    if (d[i] == 0) {
      int tm = 1;
      dfs(i, tm);
    }
  }

  for (auto& x : ans) {
    if (x.first > x.second) swap(x.first, x.second);
  }
  sort(ans.begin(), ans.end());
  
  cout << ans.size() << '\n';
  for (auto x : ans) cout << x.first << ' ' << x.second << '\n';
}