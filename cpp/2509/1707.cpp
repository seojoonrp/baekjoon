#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int v, e;
vector<int> graph[20001];
bool visited[20001];
bool color[20001];

bool bfs(int start) {
  queue<int> q;
  q.push(start);
  visited[start] = true;
  color[start] = true;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (int next : graph[cur]) {
      if (visited[next] && (color[next] == color[cur])) return false;
      else if (visited[next]) continue;

      q.push(next);
      visited[next] = true;
      color[next] = !color[cur];
    }
  }

  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tc;
  cin >> tc;

  while (tc--) {
    cin >> v >> e;
    while (e--) {
      int n1, n2;
      cin >> n1 >> n2;
      graph[n1].push_back(n2);
      graph[n2].push_back(n1);
    }

    bool is_bipartite = true;
    for (int i = 1; i <= v; ++i) {
      if (!visited[i] && !bfs(i)) is_bipartite = false;
    }

    if (is_bipartite) cout << "YES\n";
    else cout << "NO\n";

    for (int i = 1; i <= v; ++i) {
      graph[i].clear();
      visited[i] = false;
      color[i] = false;
    }
  }
}