#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

const int INF = 1e9;
const int N_MAX = 15;

int n;
int cost[N_MAX][N_MAX];
int dp[1 << N_MAX][N_MAX];

void solve() {
  dp[1][0] = 0;

  int ans = 1;

  for (int state = 1; state < (1 << n); state++) {
    for (int cur = 0; cur < n; cur++) {
      if (dp[state][cur] == INF) continue;

      int cur_cnt = 0;
      for (int i = 0; i < n; i++) {
        if (state & (1 << i)) cur_cnt++;
      }
      ans = max(ans, cur_cnt);

      for (int i = 0; i < n; i++) {
        if (state & (1 << i)) continue;

        int next_state = state | (1 << i);
        if (cost[cur][i] >= dp[state][cur]) {
          dp[next_state][i] = min(dp[next_state][i], cost[cur][i]);
        }
      }
    }
  }

  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++) {
    string row; cin >> row;
    for (int j = 0; j < n; j++) cost[i][j] = row[j] - '0';
  }

  for (int s = 0; s < (1 << N_MAX); s++) {
    for (int x = 0; x < N_MAX; x++) dp[s][x] = INF;
  }

  solve();
}