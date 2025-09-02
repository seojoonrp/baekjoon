#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MOD = 1000;

struct Island {
  int loc;
  int spring;
  bool both_side;
};

int n;
Island islands[501];
int dp[501][501]; // 첫 번째 사람이 i번째 섬을, 두 번째 사람이 j번째 섬을 밟고 i = n-1에 도달하는 경우의 수

int solve(int x, int y) {
  if (dp[x][y] != -1) return dp[x][y];

  if (x == n - 1) {
    if (islands[y].loc >= islands[x].loc - islands[x].spring) {
      return dp[x][y] = 1;
    } else return dp[x][y] = 0;
  }

  int& ret = dp[x][y];
  ret = 0;

  int next_start = max(x, y) + 1;
  for (int next = next_start; next < n; ++next) {
    if (islands[next].loc > islands[x].loc + islands[x].spring) break;
    ret = (ret + solve(next, y)) % MOD;
  }
  for (int next = next_start; next < n - 1; ++next) {
    if (islands[next].loc > islands[y].loc + islands[next].spring) continue;
    if (islands[next].both_side) ret = (ret + solve(x, next)) % MOD;
  }

  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; ++i) {
    Island& cur = islands[i];
    cin >> cur.loc >> cur.spring >> cur.both_side;
  }

  memset(dp, -1, sizeof(dp));

  cout << solve(0, 0) << '\n';
}