#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int v, e, ans;
vector<pair<int, int>> graph[10002]; // { cost, to }
bool visited[10002];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

void prim(int start) {
  pq.push({ 0, start });

  while (!pq.empty()) {
    pair<int, int> cur = pq.top();
    pq.pop();
    if (visited[cur.second]) continue;

    visited[cur.second] = true;
    ans += cur.first;

    for (auto& next : graph[cur.second]) {
      if (!visited[next.second]) pq.push(next);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> v >> e;
  while (e--) {
    int node1, node2, cost;
    cin >> node1 >> node2 >> cost;
    graph[node1].push_back({ cost, node2 });
    graph[node2].push_back({ cost, node1 });
  }

  prim(1);
  
  cout << ans << '\n';
}