#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int v, e;
vector<int> graph[10001], graph_t[10001];
stack<int> stk;
vector<vector<int>> scc;
bool visited[10001];

void dfs(int node) {
  visited[node] = true;

  for (int next : graph[node]) {
    if (!visited[next]) dfs(next);
  }

  stk.push(node);
}

void find_scc(int node, vector<int>& cur_scc) {
  visited[node] = true;

  for (int next : graph_t[node]) {
    if (!visited[next]) {
      cur_scc.push_back(next);
      find_scc(next, cur_scc);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> v >> e;
  for (int i = 0; i < e; ++i) {
    int from, to;
    cin >> from >> to;
    graph[from].push_back(to);
    graph_t[to].push_back(from);
  }

  for (int i = 1; i <= v; ++i) {
    if (!visited[i]) dfs(i);
  }

  fill(visited + 1, visited + v + 1, false);

  while (!stk.empty()) {
    int cur_root = stk.top();

    if (!visited[cur_root]) {
      vector<int> cur_scc;
      cur_scc.push_back(cur_root);
      find_scc(cur_root, cur_scc);

      sort(cur_scc.begin(), cur_scc.end());
      scc.push_back(cur_scc);
    }

    stk.pop();
  }

  sort(scc.begin(), scc.end());

  cout << scc.size() << '\n';
  for (vector<int>& cur_scc : scc) {
    for (int x : cur_scc) cout << x << ' ';
    cout << "-1\n";
  }
}