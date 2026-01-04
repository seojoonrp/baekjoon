#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

const int N_MAX = 205;
const int NUM_MAX = 2e6 + 5;
const int INF = 1e9;

struct Edge {
  int to;
  int capacity;
  int rev;
};

struct Prev {
  int from;
  int edge_idx;
};

int n, m, nodes;
int arr[N_MAX];
bool is_forced[N_MAX];
vector<Edge> graph[N_MAX];
Prev pv[N_MAX];
bool visited[N_MAX];
bool is_prime[NUM_MAX];

void add_edge(int from, int to, int capacity) {
  graph[from].push_back({ to, capacity, (int)graph[to].size() });
  graph[to].push_back({ from, 0, (int)graph[from].size() - 1 });
}

bool find_augpath(int source, int sink) {
  fill(visited, visited + nodes, false);

  queue<int> q;
  q.push(source);
  visited[source] = true;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (int i = 0; i < (int)graph[cur].size(); i++) {
      Edge& e = graph[cur][i];

      if (e.capacity > 0 && !visited[e.to]) {
        q.push(e.to);
        visited[e.to] = true;
        pv[e.to] = { cur, i };
      }
    }
  }

  return visited[sink];
}

int max_flow(int source, int sink) {
  int total_flow = 0;

  while (find_augpath(source, sink)) {
    int cur_flow = INF;

    for (int i = sink; i != source; i = pv[i].from) {
      Edge& e = graph[pv[i].from][pv[i].edge_idx];
      cur_flow = min(cur_flow, e.capacity);
    }

    for (int i = sink; i != source; i = pv[i].from) {
      Edge& e = graph[pv[i].from][pv[i].edge_idx];
      e.capacity -= cur_flow;
      graph[i][e.rev].capacity += cur_flow;
    }

    total_flow += cur_flow;
  }

  return total_flow;
}

void fill_is_prime(int M) {
  fill(is_prime, is_prime + M + 1, true);
  is_prime[0] = is_prime[1] = false;

  for (int i = 2; i <= (int)sqrt(M); i++) {
    if (!is_prime[i]) continue;

    for (int j = i * 2; j <= M; j += i) {
      is_prime[j] = false;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  int source = 0;
  int sink = n + 1;
  nodes = n + 2;

  int max_elem = -1;
  vector<int> ones;

  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
    max_elem = max(max_elem, arr[i]);

    if (arr[i] == 1) ones.push_back(i);
  }

  fill_is_prime(max_elem * 2 + 1);

  int forced = 0;
  if ((int)ones.size() > 1) {
    for (int i = 1; i < (int)ones.size(); i++) {
      int idx = ones[i];
      arr[idx] = 2;
      is_forced[idx] = true;
      forced++;
    }
  }

  for (int i = 1; i <= n; i++) {
    if (arr[i] % 2 == 1) add_edge(source, i, 1);
    else add_edge(i, sink, is_forced[i] ? INF : 1);
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i == j) continue;

      if (is_forced[i]) continue;

      int nai = (arr[i] % 2 == 0) ? arr[i] + 1 : arr[i];
      int naj = (arr[j] % 2 == 0) ? arr[j] : arr[j] + 1;

      if (is_prime[nai + naj]) add_edge(i, j, INF);
    }
  }

  int mf = max_flow(source, sink);
  cout << forced + mf << '\n';
  if (forced + mf == 0) return 0;

  fill(visited, visited + nodes, false);

  queue<int> q;
  q.push(source);
  visited[source] = true;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (Edge& e : graph[cur]) {
      if (!visited[e.to] && e.capacity > 0) {
        q.push(e.to);
        visited[e.to] = true;
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    bool changed = false;

    if (is_forced[i]) changed = true;
    else if (arr[i] % 2 == 1 && !visited[i]) changed = true;
    else if (arr[i] % 2 == 0 && visited[i]) changed = true;
    
    if (changed) cout << i << ' ';
  }
  cout << '\n';
}