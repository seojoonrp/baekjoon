#include <iostream>
#include <algorithm>
using namespace std;

int goal, n;
int money[22], customer[22];
int dp[22][1002]; // i번째 도시까지 고려했을 때, 호텔의 고객을 적어도 j명 늘리기 위해 필요한 돈의 최솟값

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> goal >> n;
  for (int i = 0; i < n; ++i) {
    cin >> money[i] >> customer[i];
  }

  for (int j = 1; j <= goal; ++j) {
    dp[0][j] = money[0] * ((j - 1) / customer[0] + 1);
  }

  for (int i = 1; i < n; ++i) {
    for (int j = 0; j <= goal; ++j) {
      if (j < customer[i]) {
        dp[i][j] = min(dp[i - 1][j], dp[i][0] + money[i]);
      } else {
        dp[i][j] = min(dp[i - 1][j], dp[i][j - customer[i]] + money[i]);
      }
    }
  }

  cout << dp[n - 1][goal] << "\n";
}