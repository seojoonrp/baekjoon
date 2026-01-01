#include <iostream>
#include <algorithm>
using namespace std;

const int N = 50 + 5;
const int MAX = 5e5 + 5;

int n;
int arr[N];
int dp[MAX], temp[MAX];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;

  int total = 0;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
    total += arr[i];
  }

  fill(dp, dp + total + 1, -1);
  dp[0] = 0;

  for (int i = 1; i <= n; i++) {
    int cur = arr[i];

    for (int j = 0; j <= total; j++) temp[j] = dp[j];

    for (int j = 0; j <= total; j++) {
      if (dp[j] == -1) continue;

      temp[j + cur] = max(temp[j + cur], dp[j] + cur);
      if (j >= cur) temp[j - cur] = max(temp[j - cur], dp[j]);
      else temp[cur - j] = max(temp[cur - j], dp[j] + (cur - j));
    }

    for (int j = 0; j <= total; j++) dp[j] = temp[j];
  }

  if (dp[0] == 0) cout << -1 << '\n';
  else cout << dp[0] << '\n';
}