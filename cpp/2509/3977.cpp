#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> graph[100001], graph_t[100001];
bool visited[100001];
int root;
vector<int> ans;

void dfs(int node) {
  visited[node] = true;

  for (int next : graph[node]) {
    if (!visited[next]) dfs(next);
  }

  root = node;
}

void vector_dfs(int node, vector<int>& vec, bool transpose) {
  visited[node] = true;

  for (int next : (transpose ? graph_t[node] : graph[node])) {
    if (!visited[next]) {
      vec.push_back(next);
      vector_dfs(next, vec, transpose);
    }
  }
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
      graph_t[to].push_back(from);
    }

    for (int i = 0; i < n; ++i) {
      if (!visited[i]) dfs(i);
    }

    fill(visited, visited + n, false);
    ans.push_back(root);
    vector_dfs(root, ans, false);

    if (ans.size() == n) {
      fill(visited, visited + n, false);
      ans.clear();
      ans.push_back(root);
      vector_dfs(root, ans, true);

      sort(ans.begin(), ans.end());
      for (int node : ans) cout << node << '\n';
    } else {
      cout << "Confused\n";
    }
    cout << '\n';

    fill(visited, visited + n, false);
    for (int i = 0; i < n; ++i) {
      graph[i].clear();
      graph_t[i].clear();
    }
    ans.clear();
  }
}