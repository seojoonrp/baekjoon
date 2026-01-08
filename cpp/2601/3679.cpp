#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

const int MAX = 2e3 + 5;
const ll INF = 1e18;

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

int n;
Point points[MAX];
Point pivot;
int pivot_idx;

ll sq(ll x) { return x * x; }

// AB, AC 외적
int ccw(Point& a, Point& b, Point& c) {
  ll val = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);

  if (val > 0) return 1;
  else if (val == 0) return 0;
  else return -1;
}

bool angle_compare(pair<Point, int>& a, pair<Point, int>& b) {
  Point pa = a.first;
  Point pb = b.first;

  Point origin = { 0, 0 };
  int ccw_val = ccw(origin, pa, pb);

  if (ccw_val == 1) return true;
  if (ccw_val == -1) return false;

  return sq(pa.x) + sq(pa.y) < sq(pb.x) + sq(pb.y);
}

void solve() {
  vector<pair<Point, int>> rel;
  for (int i = 0; i < n; i++) {
    if (points[i] == pivot) continue;
    rel.push_back({ points[i] - pivot, i });
  }

  sort(rel.begin(), rel.end(), angle_compare);

  int last = rel.size() - 1;
  int start = last;
  Point origin = { 0, 0 };

  while (start > 0 && ccw(origin, rel[start - 1].first, rel[last].first) == 0) {
    start--;
  }
  reverse(rel.begin() + start, rel.end());

  cout << pivot_idx << ' ';
  for (auto& ppi : rel) cout << ppi.second << ' ';
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tc;
  cin >> tc;

  while (tc--) {
    cin >> n;
  
    ll min_x = INF, min_y = INF;
    for (int i = 0; i < n; i++) {
      cin >> points[i].x >> points[i].y;
      if (points[i].y < min_y || (points[i].y == min_y && points[i].x < min_x)) {
        min_y = points[i].y;
        min_x = points[i].x;
        pivot = points[i];
        pivot_idx = i;
      }
    }
  
    solve();
    
    min_x = INF;
    min_y = INF;
  }
}