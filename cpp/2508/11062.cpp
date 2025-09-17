#include <iostream>
#include <algorithm>
using namespace std;

int n;
int cards[1002];
int cardsum[1002];
int dp[1002][1002];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int tc;
  cin >> tc;
  while (tc--) {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      cin >> cards[i];
      dp[i][i] = cards[i];
      cardsum[i] = cardsum[i - 1] + cards[i];
    }

    for (int len = 1; len < n; ++len) {
      for (int s = 1; s <= n - len; ++s) {
        int e = s + len;

        int score_s = cards[s] + ((cardsum[e] - cardsum[s]) - dp[s + 1][e]);
        int score_e = cards[e] + ((cardsum[e - 1] - cardsum[s - 1]) - dp[s][e - 1]);
        dp[s][e] = max(score_s, score_e);
      }
    }

    cout << dp[1][n] << '\n';

    for (int i = 1; i <= n; ++i) {
      cards[i] = cardsum[i] = 0;
      for (int j = i; j <= n; ++j) dp[i][j] = 0;
    }
  }
}