#include <iostream>
using namespace std;
using ll = long long;

struct Point {
  ll x, y;

  bool operator<=(const Point& other) {
    if (x == other.x) return y <= other.y;
    return x <= other.x;
  }
};

void swap(Point& a, Point& b) {
  Point temp = a;
  a = b;
  b = temp;
}

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

  int c1 = ccw(a1, a2, b1);
  int c2 = ccw(a1, a2, b2);
  int c3 = ccw(b1, b2, a1);
  int c4 = ccw(b1, b2, a2);

  bool ans = false;

  if (c1 * c2 <= 0 && c3 * c4 <= 0) {
    if (c1 * c2 == 0 && c3 * c4 == 0) {
      if (a2 <= a1) swap(a1, a2);
      if (b2 <= b1) swap(b1, b2);

      if (a1 <= b2 && b1 <= a2) ans = true;
    } else ans = true;
  }

  cout << (ans ? 1 : 0) << '\n';
}