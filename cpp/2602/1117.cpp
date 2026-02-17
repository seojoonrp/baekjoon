#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;

ll w, h, f, c;
ll x1, y1, x2, y2;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> w >> h >> f >> c;
  cin >> x1 >> y1 >> x2 >> y2;

  ll x = 0;
  ll shorter = min(f, w - f);
  if (x1 > shorter) x = x2 - x1;
  else if (x2 < shorter) x = 2 * (x2 - x1);
  else x = 2 * (shorter - x1) + (x2 - shorter);

  cout << w * h - x * (c + 1) * (y2 - y1) << '\n';
}