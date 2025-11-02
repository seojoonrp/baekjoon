#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 51;
const int INF = 1e9;

struct Edge {
  int to;
  int cost;
  int capacity;
  int rev;
};

struct Prev {
  int from;
  int edge_idx;
};

int n, p;
vector<Edge> graph[MAX];
Prev pv[MAX];
int max_dist[MAX], visit_count[MAX];
bool in_queue[MAX], cycle_check[MAX];
int cycle_start;

void add_edge(int from, int to, int cost, int capacity) {
  graph[from].push_back({ to, cost, capacity, (int)graph[to].size() });
  graph[to].push_back({ from, -cost, 0, (int)graph[from].size() - 1 });
}

bool SPFA() {
  fill(max_dist + 1, max_dist + n + 1, 0);
  fill(in_queue + 1, in_queue + n + 1, true);
  fill(visit_count + 1, visit_count + n + 1, 0);

  cycle_start = -1;
  bool cycle_found = false;

  queue<int> q;
  for (int i = 1; i <= n; i++) q.push(i);

  while (!q.empty() && !cycle_found) {
    int cur = q.front();
    q.pop();
    in_queue[cur] = false;

    for (int i = 0; i < (int)graph[cur].size(); i++) {
      Edge& e = graph[cur][i];

      if (e.capacity > 0 && max_dist[e.to] < max_dist[cur] + e.cost) {
        max_dist[e.to] = max_dist[cur] + e.cost;
        pv[e.to] = { cur, i };
        visit_count[e.to] = visit_count[cur] + 1;

        if (visit_count[e.to] >= n) {
          cycle_start = e.to;
          cycle_found = true;
          break;
        }

        if (!in_queue[e.to]) {
          q.push(e.to);
          in_queue[e.to] = true;
        }
      }
    }
  }

  return cycle_start != -1;
}

int maximum_profit() {
  int ans = 0;

  while (SPFA()) {
    for (int i = 1; i <= n; i++) {
      cycle_start = pv[cycle_start].from;
    }

    fill(cycle_check + 1, cycle_check + n + 1, false);
    vector<int> cycle;
    
    int cur = cycle_start;
    while (!cycle_check[cur]) {
      cycle_check[cur] = true;
      cycle.push_back(cur);
      cur = pv[cur].from;
    }

    int min_flow = INF;
    int profit_per_flow = 0;

    for (int i : cycle) {
      Edge& e = graph[pv[i].from][pv[i].edge_idx];
      min_flow = min(min_flow, e.capacity);
      profit_per_flow += e.cost;
    }

    for (int i : cycle) {
      Edge& e = graph[pv[i].from][pv[i].edge_idx];
      e.capacity -= min_flow;
      graph[i][e.rev].capacity += min_flow;
    }

    ans += min_flow * profit_per_flow;
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> p;

  for (int i = 1; i < n; i++) {
    add_edge(i, i + 1, 0, p);
  }

  int capacity[MAX][MAX] = {};
  for (int i = 1; i < n; i++) {
    for (int j = i + 1; j <= n; j++) cin >> capacity[i][j];
  }

  for (int i = 1; i < n; i++) {
    for (int j = i + 1; j <= n; j++) {
      int cost;
      cin >> cost;
      add_edge(j, i, cost, capacity[i][j]);
    }
  }

  cout << maximum_profit() << '\n';
}