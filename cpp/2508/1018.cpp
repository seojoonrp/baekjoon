#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int n, m;
string board[52];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> m;

  for (int i = 0; i < n; ++i) cin >> board[i];

  int ans = 1e9;
  for (int i = 0; i <= n - 8; ++i) {
    for (int j = 0; j <= m - 8; ++j) {
      int cur = 0;
      for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
          if (((x + y) % 2 == 0) && board[i + x][j + y] == 'B') cur++;
          if (((x + y) % 2 == 1) && board[i + x][j + y] == 'W') cur++;
        }
      }
      ans = min({ans, cur, 64 - cur});
    }
  }

  cout << ans << '\n';
}