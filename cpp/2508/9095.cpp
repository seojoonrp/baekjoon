#include <iostream>
using namespace std;

int dp[11];

int func(int n) {
  if (dp[n]) return dp[n];

  if (n == 1) return dp[1] = 1;
  if (n == 2) return dp[2] = 2;
  if (n == 3) return dp[3] = 4;

  else return dp[n] = func(n - 1) + func(n - 2) + func(n - 3);
}

int main() {
  int tc;
  cin >> tc;
  while(tc--) {
    int n;
    cin >> n;

    cout << func(n) << '\n';
  }
}