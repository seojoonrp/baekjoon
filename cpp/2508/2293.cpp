#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, k;
vector<int> coin;
int dp[10001];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    coin.push_back(x);
  }

  coin.erase(unique(coin.begin(), coin.end()), coin.end());
  sort(coin.begin(), coin.end());
  n = coin.size();

  dp[0] = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = coin[i]; j <= k; ++j) {
      dp[j] += dp[j - coin[i]];
    }
  }

  cout << dp[k] << '\n';
}