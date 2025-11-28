#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

const int MAX = 2501;
const int INF = 1e9;

int n;
string s;
bool is_pd[MAX][MAX];
int dp[MAX];

void fill_is_pd() {
  for (int i = 0; i < n; i++) is_pd[i][i] = true;
  for (int i = 0; i < n - 1; i++) {
    if (s[i] == s[i + 1]) is_pd[i][i + 1] = true;
  }
  for (int l = 2; l < n; l++) {
    for (int i = 0; i < n - l; i++) {
      int j = i + l;

      if (is_pd[i + 1][j - 1] && s[i] == s[j]) {
        is_pd[i][j] = true;
      }
    }
  }
}

int solve() {
  fill(dp, dp + n, INF);

  dp[0] = 1;

  for (int i = 1; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      if (is_pd[j][i]) {
        if (j == 0) dp[i] = 1;
        dp[i] = min(dp[i], dp[j - 1] + 1);
      }
    }
  }

  return dp[n - 1];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> s;
  n = s.length();

  fill_is_pd();

  cout << solve() << '\n';
}