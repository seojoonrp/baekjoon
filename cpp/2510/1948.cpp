#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using ll = long long;

const int MAX = 10001;

struct Edge {
  int to;
  ll dist;
};

int n, m;
vector<Edge> graph[MAX], graph_t[MAX];
int indegree[MAX];
ll max_dist[MAX];

vector<int> topology_sort() {
  vector<int> res;
  queue<int> q;

  for (int i = 1; i <= n; i++) {
    if (indegree[i] == 0) q.push(i);
  }

  while (!q.empty()) {
    int cur = q.front();
    res.push_back(cur);
    q.pop();

    for (Edge& edge : graph[cur]) {
      indegree[edge.to]--;
      if (indegree[edge.to] == 0) q.push(edge.to);
    }
  }

  return res;
}

ll solve(vector<int>& vec, int start, int dest) {
  for (int i = 1; i <= n; i++) max_dist[i] = -1;
  max_dist[start] = 0;

  for (int cur : vec) {
    if (max_dist[cur] == -1) continue;

    for (Edge& edge : graph[cur]) {
      if (max_dist[edge.to] < max_dist[cur] + edge.dist) {
        max_dist[edge.to] = max_dist[cur] + edge.dist;
      }
    }
  }

  return max_dist[dest];
}

bool visited[MAX];

int trace(int dest) {
  int res = 0;

  queue<int> q;
  q.push(dest);
  visited[dest] = true;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (Edge& edge : graph_t[cur]) {
      if (max_dist[edge.to] + edge.dist == max_dist[cur]) {
        res++;
        if (!visited[edge.to]) {
          visited[edge.to] = true;
          q.push(edge.to);
        }
      }
    }
  }

  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;

  for (int i = 0; i < m; i++) {
    int from, to, dist;
    cin >> from >> to >> dist;
    graph[from].push_back({ to, dist });
    graph_t[to].push_back({ from, dist });
    indegree[to]++;
  }

  int s, e;
  cin >> s >> e;

  vector<int> tp_sort = topology_sort();

  cout << solve(tp_sort, s, e) << '\n';
  cout << trace(e) << '\n';
}