#include <iostream>
#include <algorithm>
using namespace std;

const int N_MAX = 21;

int n;
int graph[N_MAX][N_MAX];
int ans[N_MAX][N_MAX];

bool floyd_warshall() {
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (k == i || k == j) continue;

        if (graph[i][k] + graph[k][j] < graph[i][j]) {
          return false;
        }

        if (graph[i][k] + graph[k][j] == graph[i][j]) {
          ans[i][j] = -1;
        }
      }
    }
  }

  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> graph[i][j];
      ans[i][j] = graph[i][j];
    }
  }

  bool feasible = floyd_warshall();

  if (!feasible) {
    cout << -1 << '\n';
    return 0;
  }

  int total_sum = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (ans[i][j] != -1) total_sum += ans[i][j];
    }
  }

  cout << total_sum << '\n';
}