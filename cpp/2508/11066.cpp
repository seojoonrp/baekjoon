#include <iostream>
#include <algorithm>
using namespace std;

int n;
int arrsum[503];
int dp[503][503]; // dp[i][j] = answer of arr[i] ~ arr[j]

int calculate() {
  for (int sublen = 1; sublen < n; ++sublen) {
    for (int i = 1; i <= n - sublen; ++i) {
      int ans = 1e9;

      for (int j = i; j < i + sublen; ++j) {
        int cur = dp[i][j] + dp[j + 1][i + sublen] + (arrsum[i + sublen] - arrsum[i - 1]);
        ans = min(ans, cur);
      }

      dp[i][i + sublen] = ans;
    }
  }

  return dp[1][n];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;

  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      int x;
      cin >> x;
      arrsum[i] = arrsum[i - 1] + x;
    }

    cout << calculate() << "\n";
    
    // initialize
    for (int i = 1; i <= n; ++i) {
      arrsum[i] = 0;
      for (int j = i + 1; j <= n; ++j) dp[i][j] = 0;
    }
    n = 0;
  }
}