#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 502;
const int INF = 1e9;

int n;
int arr[MAX], arr_sum[MAX];
int dp[MAX][MAX];

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

    for (int diff = 1; diff < n; diff++) {
      for (int i = 1; i <= n - diff; i++) {
        int j = i + diff;

        int min_cost = INF;
        for (int r = i; r < j; r++) {
          min_cost = min(min_cost, dp[i][r] + dp[r + 1][j]);
        }

        dp[i][j] = min_cost + arr_sum[j] - arr_sum[i - 1];
      }
    }

    cout << dp[1][n] << '\n';
  }
}