#include <iostream>
using namespace std;
using ll = long long;

const int INF = 1e9 + 1;

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

int n;
Point polygon[10001];

int ccw(const Point& a, const Point& b, const Point& c) {
  ll ret = 0;
  ret += a.x * b.y + b.x * c.y + c.x * a.y;
  ret -= a.y * b.x + b.y * c.x + c.y * a.x;
  return (ret != 0) ? (ret > 0 ? 1 : -1) : 0;
}

bool intersect(Point a1, Point a2, Point b1, Point b2) {
  int c1 = ccw(a1, a2, b1);
  int c2 = ccw(a1, a2, b2);
  int c3 = ccw(b1, b2, a1);
  int c4 = ccw(b1, b2, a2);

  if (c1 * c2 <= 0 && c3 * c4 <= 0) {
    if (c1 * c2 == 0 && c3 * c4 == 0) {
      if (a2 <= a1) swap(a1, a2);
      if (b2 <= b1) swap(b1, b2);

      if (a1 <= b2 && b1 <= a2) {
        return true;
      } else return false;
    }
    return true;
  } else return false;
}

bool inside_polygon(const Point& P) {
  int inter_cnt = 0;

  // 일직선이면서 PQ가 선분을 포함하는 경우를 막음 (그래서 y좌표에 1 더하는거)
  Point Q = { INF, P.y + 1 };

  for (int i = 0; i < n; ++i) {
    int ni = (i + 1) % n;

    // 만약 한 선분 위에 있으면 무조건 속함
    if (intersect(P, P, polygon[i], polygon[ni])) return true;

    if (intersect(P, Q, polygon[i], polygon[ni])) inter_cnt++;
  }

  return inter_cnt % 2;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; ++i) cin >> polygon[i].x >> polygon[i].y;

  for (int i = 0; i < 3; ++i) {
    Point P;
    cin >> P.x >> P.y;

    cout << (inside_polygon(P) ? 1 : 0) << '\n';
  }
}