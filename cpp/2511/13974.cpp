#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;

const int MAX = 5002;
const ll INF = 1e18;

int n;
int arr[MAX], arr_sum[MAX];
ll dp[MAX][MAX];
int opt[MAX][MAX];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tc;
  cin >> tc;

  while (tc--) {
    cin >> n;

    for (int i = 1; i <= n; i++) {
      cin >> arr[i];
      arr_sum[i] = arr_sum[i - 1] + arr[i];
    }

    for (int diff = 0; diff < n; diff++) {
      for (int i = 1; i <= n - diff; i++) {
        int j = i + diff;

        if (diff == 0) {
          dp[i][j] = 0;
          opt[i][j] = i;
          continue;
        }

        ll min_cost = INF;
        for (int r = opt[i][j - 1]; r <= min(j - 1, opt[i + 1][j]); r++) {
          if (min_cost > dp[i][r] + dp[r + 1][j]) {
            min_cost = dp[i][r] + dp[r + 1][j];
            opt[i][j] = r;
          }
        }

        dp[i][j] = min_cost + arr_sum[j] - arr_sum[i - 1];
      }
    }

    cout << dp[1][n] << '\n';
  }
}