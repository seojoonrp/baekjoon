#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1e9;

int n, m;
int dist[102][102];

void floydWarshall() {
  for (int via = 1; via <= n; ++via) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        int viaDist = dist[i][via] + dist[via][j];
        dist[i][j] = min(viaDist, dist[i][j]);
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (i != j) dist[i][j] = INF;
    }
  }

  while (m--) {
    int from, to, cost;
    cin >> from >> to >> cost;

    dist[from][to] = min(dist[from][to], cost);
  }

  floydWarshall();

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) cout << (dist[i][j] == INF ? 0 : dist[i][j]) << " ";
    cout << "\n";
  }
}