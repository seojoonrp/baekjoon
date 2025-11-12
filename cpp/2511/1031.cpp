#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int INF = 1e9;
const int MAX = 103;

int n, m, nodes;
vector<int> graph[MAX];
int cap[MAX][MAX], f[MAX][MAX];
int parent[MAX];

void add_edge(int from, int to, int capacity) {
  graph[from].push_back(to);
  graph[to].push_back(from);
  cap[from][to] = capacity;
}

bool find_augpath(int source, int sink) {
  fill(parent, parent + nodes, -1);

  queue<int> q;
  q.push(source);
  parent[source] = source;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (int next : graph[cur]) {
      if (cap[cur][next] - f[cur][next] > 0 && parent[next] == -1) {
        parent[next] = cur;
        q.push(next);
      }
    }
  }

  return parent[sink] != -1;
}

int max_flow(int source, int sink) {
  int total_flow = 0;

  while (find_augpath(source, sink)) {
    int cur_flow = INF;

    for (int i = sink; i != source; i = parent[i]) {
      int from = parent[i];
      cur_flow = min(cur_flow, cap[from][i] - f[from][i]);
    }

    for (int i = sink; i != source; i = parent[i]) {
      int from = parent[i];
      f[from][i] += cur_flow;
      f[i][from] -= cur_flow;
    }

    total_flow += cur_flow;
  }

  return total_flow;
}

bool find_new_augpath(int ji, int hi) {
  fill(parent, parent + nodes, -1);

  queue<int> q;
  q.push(ji);
  parent[ji] = ji;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    if (cur < ji) continue;

    for (int next : graph[cur]) {
      if (cur == ji && next <= hi) continue;

      if (cap[cur][next] - f[cur][next] > 0 && parent[next] == -1) {
        parent[next] = cur;
        q.push(next);
      }
    }
  }

  return parent[hi] != -1;
}

void change_flow(int ji, int hi) {
  f[ji][hi] = 0;
  f[hi][ji] = 0;

  if (find_new_augpath(ji, hi)) {
    int cur_flow = INF;

    for (int i = hi; i != ji; i = parent[i]) {
      int from = parent[i];
      cur_flow = min(cur_flow, cap[from][i] - f[from][i]);
    }

    for (int i = hi; i != ji; i = parent[i]) {
      int from = parent[i];
      f[from][i] += cur_flow;
      f[i][from] -= cur_flow;
    }
  } else {
    f[ji][hi] = 1;
    f[hi][ji] = -1;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  nodes = n + m + 2;
  int source = 0;
  int sink = n + m + 1;

  int j_total = 0;
  int h_total = 0;

  for (int i = 1; i <= n; i++) {
    int cap;
    cin >> cap;
    add_edge(source, i, cap);
    j_total += cap;
  }
  for (int i = 1; i <= m; i++) {
    int cap;
    cin >> cap;
    add_edge(n + i, sink, cap);
    h_total += cap;
  }

  if (j_total != h_total) {
    cout << -1 << '\n';
    return 0;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      add_edge(i, n + j, 1);
    }
  }

  int mf = max_flow(source, sink);
  if (mf != j_total) {
    cout << -1 << '\n';
    return 0;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (f[i][n + j] == 1) change_flow(i, n + j);
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (f[i][n + j] == 1) cout << 1;
      else cout << 0;
    }
    cout << '\n';
  }
}