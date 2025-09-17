#include <iostream>
using namespace std;

const int MOD = 1e9;

int n;
long dp[102][10][1 << 10]; // dp[len][last][mask] : mask의 숫자를 포함하고, last로 끝나는 len 길이의 계단수 개수

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;

  for (int last = 1; last <= 9; ++last) {
    dp[1][last][1 << last] = 1;
  }

  for (int len = 1; len < n; ++len) {
    for (int last = 0; last <= 9; ++last) {
      for (int mask = 0; mask < (1 << 10); ++mask) {
        if (last > 0) {
          int next = last - 1;
          dp[len + 1][next][mask | (1 << next)] += dp[len][last][mask];
          dp[len + 1][next][mask | (1 << next)] %= MOD;
        }
        if (last < 9) {
          int next = last + 1;
          dp[len + 1][next][mask | (1 << next)] += dp[len][last][mask];
          dp[len + 1][next][mask | (1 << next)] %= MOD;
        }
      }
    }
  }

  int ans = 0;
  for (int last = 0; last <= 9; ++last) {
    ans += dp[n][last][(1 << 10) - 1];
    ans %= MOD;
  }

  cout << ans << '\n';
}