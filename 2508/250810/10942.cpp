#include <iostream>
using namespace std;

int n, m;
int arr[2002];
bool dp[2002][2002];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> arr[i];

  for (int i = 1; i <= n; ++i) dp[i][i] = true;
  for (int i = 1; i < n; ++i) {
    if (arr[i] == arr[i + 1]) dp[i][i + 1] = true;
  }

  for (int l = 2; l < n; ++l) {
    for (int s = 1; s <= n - l; ++s) {
      int e = s + l;
      if (dp[s + 1][e - 1] && (arr[s] == arr[e])) dp[s][e] = true;
    }
  }

  cin >> m;
  while (m--) {
    int s, e;
    cin >> s >> e;
    cout << dp[s][e] << '\n';
  }
}