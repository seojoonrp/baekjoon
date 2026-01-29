#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;

const int MAX = 10;

int n, m;
int arr[MAX][MAX];
int ans = -1;

bool is_square(int n) {
  int sqn = sqrt(n);
  return sqn * sqn == n;
}

bool is_safe(int x, int y) {
  if (x <= 0 || x > n) return false;
  if (y <= 0 || y > m) return false;
  return true;
}

void solve(int dx, int dy) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      int cur = 0;
      int x = i, y = j;

      while (is_safe(x, y)) {
        cur = 10 * cur + arr[x][y];
        if (is_square(cur)) ans = max(ans, cur);
        x += dx;
        y += dy;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    string row; cin >> row;
    for (int j = 1; j <= m; j++) arr[i][j] = row[j - 1] - '0';
  }

  if (n == 1 && m == 1) {
    if (is_square(arr[1][1])) cout << arr[1][1] << '\n';
    else cout << -1 << '\n';
    return 0;
  }

  for (int dx = 0; dx < n; dx++) {
    for (int dy = 0; dy < m; dy++) {
      if (dx == 0 && dy == 0) continue;

      solve(dx, dy);
      solve(dx, -dy);
      solve(-dx, dy);
      solve(-dx, -dy);
    }
  }

  cout << ans << '\n';
}