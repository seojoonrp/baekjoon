#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 301;
const int INF = 1e9;

int n, source;
int graph[MAX][MAX];
int dist[MAX];
bool visited[MAX];

int prim() {
  int ans = 0;
  visited[source] = true;

  for (int i = 0; i < source; i++) {
    dist[i] = graph[source][i];
  }

  for (int cnt = 1; cnt <= source; cnt++) {
    int min_cost = INF;
    int min_idx = -1;

    for (int i = 0; i <= source; i++) {
      if (visited[i]) continue;

      if (dist[i] < min_cost) {
        min_cost = dist[i];
        min_idx = i;
      }
    }

    visited[min_idx] = true;
    ans += min_cost;

    for (int i = 0; i <= source; i++) {
      if (!visited[i]) {
        dist[i] = min(dist[i], graph[min_idx][i]);
      }
    }
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  source = n;

  for (int i = 0; i < n; i++) {
    cin >> graph[source][i];
    graph[i][source] = graph[source][i];
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cin >> graph[i][j];
  }

  cout << prim() << '\n';
}