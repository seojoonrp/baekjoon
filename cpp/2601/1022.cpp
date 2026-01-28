#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const int R_MAX = 49 + 5;
const int C_MAX = 4 + 5;

int num[C_MAX][R_MAX];
int dig[C_MAX][R_MAX];

int f(int x, int y) {
  int d = max(abs(x), abs(y));
  int rb = (2 * d + 1) * (2 * d + 1);

  if (y < x && y <= -x) return rb - (d - x);
  else if (y >= x && y < -x) return (rb - 2 * d) - (d + y);
  else if (y > x && y >= -x) return (rb - 4 * d) - (d + x);
  else return (rb - 6 * d) - (d - y);
}

int digit(int n) {
  int res = 0;
  while (n > 0) {
    n /= 10;
    res++;
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int r1, c1, r2, c2;
  cin >> r1 >> c1 >> r2 >> c2;
  // r이 y좌표, c가 x좌표

  int max_digit = -1;
  for (int y = 0; y <= r2 - r1; y++) {
    for (int x = 0; x <= c2 - c1; x++) {
      int n = f(x + c1, -(y + r1));
      num[x][y] = n;
      dig[x][y] = digit(n);
      max_digit = max(max_digit, dig[x][y]);
    }
  }

  for (int y = 0; y <= r2 - r1; y++) {
    for (int x = 0; x <= c2 - c1; x++) {
      for (int d = dig[x][y]; d < max_digit; d++) {
        cout << ' ';
      }
      cout << num[x][y];
      
      if (x == c2 - c1) cout << '\n';
      else cout << ' ';
    }
  }
}