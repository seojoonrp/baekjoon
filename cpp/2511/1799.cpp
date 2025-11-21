#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 10;

int n;
int board[MAX][MAX];
int not_safe[MAX][MAX];
int ans[2];

void fill_not_safe(int x, int y, int delta) {
  for (int i = 1; (x + i < n && y + i < n); i++) {
    not_safe[x + i][y + i] += delta;
  }
  for (int i = 1; (x + i < n && y - i >= 0); i++) {
    not_safe[x + i][y - i] += delta;
  }
}

void solve(int x, int y, int cur_cnt, int color) {
  if (y >= n) {
    x++;
    if (x >= n) {
      ans[color] = max(ans[color], cur_cnt);
      return;
    }

    if (x % 2 == 0) y = color;
    else y = 1 - color;
  }

  if (board[x][y] == 0 || not_safe[x][y] != 0) {
    solve(x, y + 2, cur_cnt, color);
    return;
  }

  fill_not_safe(x, y, 1);
  solve(x, y + 2, cur_cnt + 1, color);
  fill_not_safe(x, y, -1);
  solve(x, y + 2, cur_cnt, color);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cin >> board[i][j];
  }

  solve(0, 0, 0, 0);
  solve(0, 1, 0, 1);

  cout << ans[0] + ans[1] << '\n';
}