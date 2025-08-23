#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
vector<int> graph[1002];
bool visited[1002];

int spanningTree(int start) {
  int ans = 0;
  queue<int> q;
  
  q.push(start);
  visited[start] = true;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (auto& next : graph[cur]) {
      if (!visited[next]) {
        visited[next] = true;
        q.push(next);
        ans++;
      }
    }
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int tc;
  cin >> tc;

  while (tc--) {
    cin >> n >> m;
    while (m--) {
      int from, to;
      cin >> from >> to;
      graph[from].push_back(to);
      graph[to].push_back(from);
    }

    cout << spanningTree(1) << '\n';

    for (int i = 1; i <= n; ++i) {
      graph[i].clear();
      visited[i] = false;
    }
  }
}