#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;
using ll = long long;

const int MAX = 2e5 + 5;
const int INF = 1e9;
const double PI = 3.14159265358979;

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

int n, l;
Point points[MAX];
Point pivot;

ll sq(ll x) { return x * x; }

// AB, AC 외적
int ccw(Point& a, Point& b, Point& c) {
  ll val = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);

  if (val > 0) return 1;
  else if (val == 0) return 0;
  else return -1;
}

ll area(Point& a, Point& b, Point& c) {
  ll val = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
  return abs(val);
}

bool angle_compare(Point& a, Point& b) {
  Point origin = { 0, 0 };
  int ccw_val = ccw(origin, a, b);

  if (ccw_val == 1) return true;
  if (ccw_val == -1) return false;

  return sq(a.x) + sq(a.y) < sq(b.x) + sq(b.y);
}

vector<Point> convex_hull() {
  vector<Point> rel;
  for (int i = 1; i <= n; i++) {
    if (points[i] == pivot) continue;
    rel.push_back(points[i] - pivot);
  }

  sort(rel.begin(), rel.end(), angle_compare);

  vector<Point> stk;
  stk.push_back({ 0, 0 });

  for (Point& p : rel) {
    while (stk.size() >= 2) {
      int l = stk.size();
      if (ccw(stk[l - 2], stk[l - 1], p) <= 0) {
        stk.pop_back();
      } else break;
    }
    
    stk.push_back(p);
  }

  for (Point& p : stk) {
    p.x += pivot.x;
    p.y += pivot.y;
  }

  return stk;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> l;

  int min_x = INF, min_y = INF;
  for (int i = 1; i <= n; i++) {
    cin >> points[i].x >> points[i].y;
    if (points[i].y < min_y || (points[i].y == min_y && points[i].x < min_x)) {
      min_y = points[i].y;
      min_x = points[i].x;
      pivot = points[i];
    }
  }

  vector<Point> ch = convex_hull();

  double ans = 0;
  for (int i = 0; i < (int)ch.size(); i++) {
    Point p1 = ch[i];
    Point p2 = ch[(i + 1) % ch.size()];
    ans += sqrt(sq(p1.x - p2.x) + sq(p1.y - p2.y));
  }
  ans += 2 * PI * (double)l;

  cout << fixed << setprecision(0) << ans << '\n';
}