#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> graph[1002];
bool visited[1002];
int ans;

void dfs(int x) {
  if (visited[x]) return;

  visited[x] = true;

  for (auto& next : graph[x]) {
    if (!visited[next]) dfs(next);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> m;
  while (m--) {
    int node1, node2;
    cin >> node1 >> node2;
    graph[node1].push_back(node2);
    graph[node2].push_back(node1);
  }

  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      dfs(i);
      ans++;
    }
  }

  cout << ans << '\n';
}