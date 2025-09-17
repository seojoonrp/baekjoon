#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int n, m;
vector<int> graph[100001];
bool visited[100001];
stack<int> stk;

void dfs(int node, bool do_push) {
  visited[node] = true;

  for (int next : graph[node]) {
    if (!visited[next]) dfs(next, do_push);
  }

  if (do_push) stk.push(node);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tc;
  cin >> tc;

  while (tc--) {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
      int from, to;
      cin >> from >> to;
      graph[from].push_back(to);
    }

    for (int i = 1; i <= n; ++i) {
      if (!visited[i]) dfs(i, true);
    }

    fill(visited + 1, visited + n + 1, false);

    int ans = 0;
    while (!stk.empty()) {
      int cur_root = stk.top();

      if (!visited[cur_root]) {
        ans++;
        dfs(cur_root, false);
      }

      stk.pop();
    }

    cout << ans << '\n';

    for (int i = 1; i <= n; ++i) {
      graph[i].clear();
      visited[i] = false;
    }
  }
}