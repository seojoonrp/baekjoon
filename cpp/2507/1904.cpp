#include <iostream>
using namespace std;

int dp[1000002];

int fibo(int n) {
  if (dp[n] != 0) return dp[n];

  if (n == 1 || n == 0) return dp[n] = 1;

  return dp[n] = (fibo(n - 1) + fibo(n - 2)) % 15746;
}

int main() {
  int n;
  cin >> n;

  cout << fibo(n) << endl;
}