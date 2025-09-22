#include <cstdio>
#include <algorithm>
using namespace std;

const int INF = 2e9;

int n, t, m;
int prev_dist[10000], cur_dist[10000];
int s, e;

void calc_dp(int n1, int n2, int dist) {
  if (prev_dist[n1] != INF) {
    cur_dist[n2] = min(cur_dist[n2], prev_dist[n1] + dist);
  }
}

int main() {
  scanf("%d %d %d", &n, &t, &m);
  scanf("%d %d", &s, &e);

  fill(prev_dist, prev_dist + n, INF);
  prev_dist[s] = 0;

  for (int time = 0; time < t; time++) {
    for (int i = 0; i < n; i++) {
      cur_dist[i] = prev_dist[i];
    }

    for (int edge = 0; edge < m; edge++) {
      int n1, n2, dist;
      scanf("%d %d %d", &n1, &n2, &dist);

      calc_dp(n1, n2, dist);
      calc_dp(n2, n1, dist);
    }

    for (int i = 0; i < n; i++) {
      prev_dist[i] = cur_dist[i];
    }
  }

  printf("%d\n", (prev_dist[e] == INF ? -1 : prev_dist[e]));
}