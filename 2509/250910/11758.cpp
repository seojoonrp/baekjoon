#include <iostream>
using namespace std;

struct Point {
  int x, y;
};

int CCW(const Point& a, const Point& b, const Point& c) {
  int ret = 0;
  ret += (a.x * b.y + b.x * c.y + c.x * a.y);
  ret -= (a.y * b.x + b.y * c.x + c.y * a.x);
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  Point a, b, c;
  cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;

  int ccw = CCW(a, b, c);

  if (ccw > 0) cout << "1\n";
  else if (ccw < 0) cout << "-1\n";
  else cout << "0\n";
}