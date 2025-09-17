#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, max_weight;
int weight[31];
bool dp[31][40001];

void solve() {
  dp[0][0] = dp[0][weight[0]] = true;

  for (int i = 1; i < n; ++i) {
    for (int j = 0; j <= max_weight; ++j) {
      if (dp[i - 1][j]) dp[i][j] = true;

      if (j < weight[i]) {
        if (dp[i - 1][weight[i] - j] || dp[i - 1][j + weight[i]]) dp[i][j] = true;
      } else if (j <= max_weight - weight[i]) {
        if (dp[i - 1][j - weight[i]] || dp[i - 1][j + weight[i]]) dp[i][j] = true;
      } else {
        if (dp[i - 1][j - weight[i]]) dp[i][j] = true;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> weight[i];
    max_weight += weight[i];
  }

  solve();

  int tc;
  cin >> tc;
  while (tc--) {
    int x;
    cin >> x;
    if (dp[n - 1][x]) cout << "Y ";
    else cout << "N ";
  }
  cout << '\n';
}