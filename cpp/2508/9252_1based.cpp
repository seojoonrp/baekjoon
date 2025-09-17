#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string a, b;
int n, m;
int dp[1003][1003];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> a >> b;
  n = a.length();
  m = b.length();

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
      else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    }
  }

  cout << dp[n][m] << '\n';
  if (dp[n][m] == 0) return 0;

  string ans;
  int x = n, y = m;

  while (x > 0 && y > 0) {
    if (a[x - 1] == b[y - 1]) {
      ans += a[x - 1];
      --x;
      --y;
    } else if (dp[x - 1][y] >= dp[x][y - 1]) {
      --x;
    } else {
      --y;
    }
  }
  
  reverse(ans.begin(), ans.end());
  cout << ans << '\n';
}