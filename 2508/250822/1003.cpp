#include <iostream>
using namespace std;

int n;
int zerodp[41], onedp[41];

int zero(int n) {
  if (n == 0) return zerodp[0] = 1;
  if (n == 1) return zerodp[1] = 0;

  if (zerodp[n]) return zerodp[n];

  return zerodp[n] = zero(n - 1) + zero(n - 2);
}
int one(int n) {
  if (n == 0) return onedp[0] = 0;
  if (n == 1) return onedp[1] = 1;

  if (onedp[n]) return onedp[n];

  return onedp[n] = one(n - 1) + one(n - 2);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    cout << zero(n) << ' ' << one(n) << '\n';
  }
}