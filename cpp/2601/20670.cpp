#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;

const int INF = 1e9 + 5;

struct Point {
  ll x;
  ll y;

  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }

  Point operator-(const Point& other) const {
    Point res;
    res.x = x - other.x;
    res.y = y - other.y;
    return res;
  }
};

Point origin = { 0, 0 };

int A, B, n;
vector<Point> a, b;
Point pivot_a, pivot_b;

ll ccw(Point& a, Point& b, Point& c) {
  ll val = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
  return val;
}

bool angle_compare(Point& a, Point& b) {
  ll ccw_val = ccw(origin, a, b);

  if (ccw_val > 0) return true;
  if (ccw_val < 0) return false;

  return a.x * a.x + a.y * a.y < b.x * b.x + b.y * b.y;
}

// -1, 0, 1 = 외부, 경계, 내부
int inside(vector<Point>& points, Point X) {
  int P = points.size();

  if (ccw(origin, points[1], X) < 0) return -1;
  if (ccw(origin, points[P - 1], X) > 0) return -1;

  int lo = 1, hi = P - 1;
  while (lo + 1 < hi) {
    int mid = (lo + hi) / 2;

    if (ccw(origin, points[mid], X) >= 0) lo = mid;
    else hi = mid;
  }

  ll res = ccw(points[lo], points[lo + 1], X);
  if (res > 0) return 1;
  if (res == 0) return 0;
  return -1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> A >> B >> n;
  a.resize(A);
  b.resize(B);

  int min_x = INF, min_y = INF;
  for (int i = 0; i < A; i++) {
    cin >> a[i].x >> a[i].y;
    if (a[i].y < min_y || (a[i].y == min_y && a[i].x < min_x)) {
      min_y = a[i].y;
      min_x = a[i].x;
      pivot_a = a[i];
    }
  }

  min_x = INF, min_y = INF;
  for (int i = 0; i < B; i++) {
    cin >> b[i].x >> b[i].y;
    if (b[i].y < min_y || (b[i].y == min_y && b[i].x < min_x)) {
      min_y = b[i].y;
      min_x = b[i].x;
      pivot_b = b[i];
    }
  }

  for (int i = 0; i < A; i++) a[i] = a[i] - pivot_a;
  for (int i = 0; i < B; i++) b[i] = b[i] - pivot_b;

  sort(a.begin(), a.end(), angle_compare);
  sort(b.begin(), b.end(), angle_compare);

  int ans = 0;
  while (n--) {
    Point X;
    cin >> X.x >> X.y;

    int a_res = inside(a, X - pivot_a);
    int b_res = inside(b, X - pivot_b);

    if (a_res <= 0 || b_res >= 0) ans++;
  }

  if (ans == 0) cout << "YES" << '\n';
  else cout << ans << '\n';
}