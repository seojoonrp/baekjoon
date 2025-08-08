#include <iostream>
using namespace std;

long long dp[102];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  dp[1] = dp[2] = dp[3] = 1;
  dp[4] = dp[5] = 2;
  for (int i = 6; i <= 100; ++i) dp[i] = dp[i - 1] + dp[i - 5];

  int t;
  cin >> t;
  
  for (int i = 0; i < t; ++i) {
    int n;
    cin >> n;

    cout << dp[n] << "\n";
  }
}