#include <iostream>
using namespace std;
using ll = long long;

struct Point {
  ll x, y;
};

int ccw(const Point& a, const Point& b, const Point& c) {
  ll ret = 0;
  ret += a.x * b.y + b.x * c.y + c.x * a.y;
  ret -= a.y * b.x + b.y * c.x + c.y * a.x;
  return (ret != 0) ? (ret > 0 ? 1 : -1) : 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  Point a1, a2, b1, b2;
  cin >> a1.x >> a1.y >> a2.x >> a2.y;
  cin >> b1.x >> b1.y >> b2.x >> b2.y;

  bool ans = true;
  if (ccw(a1, a2, b1) * ccw(a1, a2, b2) > 0) ans = false;
  if (ccw(b1, b2, a1) * ccw(b1, b2, a2) > 0) ans = false;

  cout << (ans ? 1 : 0) << '\n';
}