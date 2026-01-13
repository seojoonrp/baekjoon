#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
using ld = long double;

struct Line {
  int idx;
  ll a, b;
};

int n, m;
int maxy, miny;
vector<Line> lines;

bool line_cmp(const Line& l1, const Line& l2) {
  if (l1.a == l2.a) return l1.b < l2.b;
  return l1.a > l2.a;
}

// Assume no parallel input
ld intersect_x(Line& l1, Line& l2) {
  return (ld)(l2.b - l1.b) / (ld)(l1.a - l2.a);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> maxy >> miny;

  cin >> n;
  lines.resize(n);

  for (int i = 0; i < n; i++) {
    ll upx, lowx;
    cin >> upx >> lowx;
    lines[i].idx = i + 1;
    lines[i].a = upx - lowx;
    lines[i].b = lowx;
  }

  sort(lines.begin(), lines.end(), line_cmp);

  vector<Line> hull;
  for (Line& cur : lines) {
    if (!hull.empty() && hull.back().a == cur.a) continue;

    while (hull.size() >= 2) {
      Line first = hull.back();
      Line second = hull[hull.size() - 2];

      if (intersect_x(first, second) >= intersect_x(first, cur)) {
        hull.pop_back();
      } else {
        break;
      }
    }

    hull.push_back(cur);
  }

  vector<ld> interx;
  for (int i = 0; i < (int)hull.size() - 1; i++) {
    interx.push_back(intersect_x(hull[i], hull[i + 1]));
  }

  cin >> m;
  while (m--) {
    ld y; cin >> y;
    ld t = (y - (ld)miny) / (ld)(maxy - miny);

    int idx = upper_bound(interx.begin(), interx.end(), t) - interx.begin();
    cout << hull[idx].idx << '\n';
  }
}