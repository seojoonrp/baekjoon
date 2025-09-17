#include <iostream>
#include <algorithm>
using namespace std;

struct Point {
  int x;
  int y;
};

bool compare(const Point& a, const Point& b) {
  if (a.x != b.x) return a.x < b.x;
  return a.y < b.y;
}

int n;
Point points[100002];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 0; i < n; ++i) cin >> points[i].x >> points[i].y;

  sort(points, points + n, compare);

  for (int i = 0; i < n; ++i) cout << points[i].x << ' ' << points[i].y << '\n';
}