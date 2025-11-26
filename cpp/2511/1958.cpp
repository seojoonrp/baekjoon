#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int MAX = 102;

int la, lb, lc;
string a, b, c;
int dp[MAX][MAX][MAX];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> a >> b >> c;
  la = a.length();
  lb = b.length();
  lc = c.length();

  for (int i = 1; i <= la; i++) {
    for (int j = 1; j <= lb; j++) {
      for (int k = 1; k <= lc; k++) {
        if (a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1]) {
          dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
        } else {
          dp[i][j][k] = max({ dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1] });
        }
      }
    }
  }

  cout << dp[la][lb][lc] << '\n';
}