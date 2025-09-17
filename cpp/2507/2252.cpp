#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

int n, m;
int indegree[32002];
vector<int> graph[32002];

void topologySort() {
  queue<int> q;

  for (int i = 1; i <= n; ++i) {
    if (indegree[i] == 0) q.push(i);
  }

  while (!q.empty()) {
    int cur = q.front();
    cout << cur << " ";
    q.pop();

    for (auto& next : graph[cur]) {
      indegree[next]--;
      if (indegree[next] == 0) q.push(next);
    }
  }

  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> m;

  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    graph[x].push_back(y);
    indegree[y]++;
  }

  topologySort();
}