#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 10001;

int n, m, tm;
vector<int> graph[MAX];
int d[MAX], parent[MAX], low[MAX];
vector<int> ans;

void dfs(int cur) {
  d[cur] = tm;
  low[cur] = tm;
  tm++;

  int child_cnt = 0;

  for (int next : graph[cur]) {
    if (parent[cur] == next) continue;

    if (d[next] == 0) {
      child_cnt++;
      parent[next] = cur;
      dfs(next);

      if (parent[cur] == 0) {
        if (child_cnt >= 2) ans.push_back(cur);
      } else {
        if (d[cur] <= low[next]) ans.push_back(cur);
      }

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
      tm = 1;
      dfs(i);
    }
  }

  sort(ans.begin(), ans.end());
  ans.erase(unique(ans.begin(), ans.end()), ans.end());
  
  cout << ans.size() << '\n';
  for (int x : ans) cout << x << ' ';
  cout << '\n';
}