#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;
using ll = long long;

const int MAX = 21;
const double INF = 1e9;

struct Point {
  ll x, y;

  Point operator+(const Point& other) const {
    return {x + other.x, y + other.y};
  }
  Point operator-(const Point& other) const {
    return {x - other.x, y - other.y};
  }
};

int n;
Point points[MAX];
double ans = INF;

ll sq(ll x) { return x * x; }

void update_ans(vector<int>& selected) {
  bool sel[MAX] = {false};
  for (int s : selected) sel[s] = true;

  Point p = {0, 0}, m = {0, 0};
  for (int i = 1; i <= n; i++) {
    if (sel[i]) p = p + points[i];
    else m = m + points[i];
  }
  Point res = p - m;

  ans = min(ans, sqrt(sq(res.x) + sq(res.y)));
}

void solve(vector<int>& selected) {
  if ((int)selected.size() >= n / 2) {
    update_ans(selected);
    return;
  }

  int i;
  if (selected.empty()) i = 1;
  else i = selected.back() + 1;
  for (; i <= n; i++) {
    selected.push_back(i);
    solve(selected);
    selected.pop_back();
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cout << fixed;
  cout.precision(8);

  int tc; cin >> tc;
  while (tc--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> points[i].x >> points[i].y;
    }

    vector<int> selected;
    solve(selected);
    cout << ans << '\n';

    ans = INF;
  }
}