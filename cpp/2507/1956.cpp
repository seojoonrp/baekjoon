#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1e9;

int n, m;
int dist[402][402];

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

  int ans = INF;
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      if (dist[i][j] == INF || dist[j][i] == INF) continue;

      int cycleDist = dist[i][j] + dist[j][i];
      ans = min(ans, cycleDist);
    }
  }

  cout << (ans == INF ? -1 : ans) << "\n";
}