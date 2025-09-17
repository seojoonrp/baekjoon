#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int n, m, start;
vector<int> graph[100002];
queue<int> q;
int res[100002];
int cnt = 1;

void bfs(int start) {
  q.push(start);
  res[start] = cnt++;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (int i = 0; i < graph[cur].size(); ++i) {
      if (res[graph[cur][i]] == 0) {
        q.push(graph[cur][i]);
        res[graph[cur][i]] = cnt++;
      }
    }
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

  bfs(start);

  for (int i = 1; i <= n; ++i) cout << res[i] << "\n";
}