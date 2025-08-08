#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m, start;
vector<int> graph[100002];
int res[100002];
int cnt = 1;

void dfs(int x) {
  res[x] = cnt++;

  for (int i = 0; i < graph[x].size(); ++i) {
    if (res[graph[x][i]] == 0) dfs(graph[x][i]);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> m >> start;
  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }
  for (int i = 1; i <= n; ++i) sort(graph[i].begin(), graph[i].end());

  dfs(start);

  for (int i = 1; i <= n; ++i) cout << res[i] << "\n";
}