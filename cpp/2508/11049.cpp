#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

int n;
int row[502];
int col[502];
int dp[502][502];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 0; i < n; ++i) cin >> row[i] >> col[i];

  for (int sublen = 1; sublen < n; ++sublen) {
    for (int start = 0; start < n - sublen; ++start) {
      int end = start + sublen;
      dp[start][end] = INT_MAX;

      for (int mid = start; mid < end; ++mid) {
        int cur = dp[start][mid] + dp[mid + 1][end] + row[start] * col[mid] * col[end];
        dp[start][end] = min(dp[start][end], cur);
      }
    }
  }

  cout << dp[0][n - 1] << "\n";
}