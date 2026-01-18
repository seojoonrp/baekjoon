#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const int INF = 1e9;

int dp[5][5];
int nxt[5][5];

int power(int from, int to) {
  if (from == 0) return 2;
  if (from == to) return 1;
  if (abs(to - from) == 2) return 4;
  return 3;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      dp[i][j] = INF;
      nxt[i][j] = INF;
    }
  }
  dp[0][0] = 0;

  while (true) {
    int x; cin >> x;
    if (x == 0) break;

    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (dp[i][j] == INF) continue;

        if (i == x || j == x) {
          nxt[i][j] = min(nxt[i][j], dp[i][j] + 1);
        } else {
          nxt[i][x] = min(nxt[i][x], dp[i][j] + power(j, x));
          nxt[x][j] = min(nxt[x][j], dp[i][j] + power(i, x));
        }
      }
    }

    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        dp[i][j] = nxt[i][j];
        nxt[i][j] = INF;
      }
    }
  }

  int ans = INF;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      ans = min(ans, dp[i][j]);
    }
  }
  cout << ans << '\n';
}