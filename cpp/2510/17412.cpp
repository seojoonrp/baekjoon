#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;

int n, m;
vector<int> graph[401];
int flow[401][401];
int capacity[401][401];
int parent[401];

int maximum_flow(int START, int END) {
  int ans = 0;

  while (true) {
    fill(parent + 1, parent + n + 1, -1);

    queue<int> q;
    q.push(START);
    parent[START] = START;

    while (!q.empty()) {
      int cur = q.front();
      q.pop();

      for (int next : graph[cur]) {
        if (capacity[cur][next] - flow[cur][next] > 0 && parent[next] == -1) {
          q.push(next);
          parent[next] = cur;
          if (next == END) break;
        }
      }
    }

    if (parent[END] == -1) break;

    int cur_min_flow = INF;
    for (int i = END; i != START; i = parent[i]) {
      int prev = parent[i];
      cur_min_flow = min(cur_min_flow, capacity[prev][i] - flow[prev][i]);
    }

    for (int i = END; i != START; i = parent[i]) {
      int prev = parent[i];
      flow[prev][i] += cur_min_flow;
      flow[i][prev] -= cur_min_flow;
    }

    ans += cur_min_flow;
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
    capacity[a][b] = 1;
  }

  cout << maximum_flow(1, 2) << '\n';
}