#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 503;
const int INF = 1e9;

int n, source, sink, nodes;
vector<int> graph[MAX];
int capacity[MAX][MAX], flow[MAX][MAX];
int level[MAX], index[MAX];
bool visited[MAX];

bool find_level() {
  fill(level + 1, level + nodes + 1, -1);
  
  queue<int> q;
  q.push(source);
  level[source] = 0;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (int next : graph[cur]) {
      if (level[next] == -1 && capacity[cur][next] - flow[cur][next] > 0) {
        q.push(next);
        level[next] = level[cur] + 1;
      }
    }
  }

  if (level[sink] == -1) return false;
  return true;
}

int blocking_flow(int cur, int cur_flow) {
  if (cur == sink) return cur_flow;
  
  for (int& i = index[cur]; i < graph[cur].size(); i++) {
    int next = graph[cur][i];

    if (level[next] == level[cur] + 1 && capacity[cur][next] - flow[cur][next] > 0) {
      int min_flow = blocking_flow(next, min(capacity[cur][next] - flow[cur][next], cur_flow));

      if (min_flow > 0) {
        flow[cur][next] += min_flow;
        flow[next][cur] -= min_flow;
        return min_flow;
      }
    }
  }

  return 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  source = n + 1;
  sink = n + 2;
  nodes = n + 2;

  for (int i = 1; i <= n; i++) {
    int team;
    cin >> team;
    if (team == 1) {
      capacity[source][i] = INF;
      graph[source].push_back(i);
      graph[i].push_back(source);
    }
    if (team == 2) {
      capacity[i][sink] = INF;
      graph[sink].push_back(i);
      graph[i].push_back(sink);
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> capacity[i][j];
      if (i != j) graph[i].push_back(j);
    }
  }

  int total_sad = 0;
  while (find_level()) {
    fill(index + 1, index + nodes + 1, 0);

    while (true) {
      int bf = blocking_flow(source, INF);
      if (bf == 0) break;

      total_sad += bf;
    }
  }

  cout << total_sad << '\n';

  find_level();
  for (int i = 1; i <= n; i++) {
    if (level[i] != -1) cout << i << ' ';
  }
  cout << '\n';
  for (int i = 1; i <= n; i++) {
    if (level[i] == -1) cout << i << ' ';
  }
  cout << '\n';
}