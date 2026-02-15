#include <iostream>
#include <cmath>
#include <algorithm>
#include <sstream>
using namespace std;

double solve(double dist, double d, double t) {
  if (d <= t) return dist;

  if (dist < d) {
    return min({dist, t + (d - dist), 2.0 * t});
  }

  int d_cnt = (int)(dist / d);
  double left = dist - (double)(d * d_cnt);

  return min({
    dist,
    d_cnt * t + left,
    (d_cnt + 1) * t + (d - left),
    (double)(d_cnt + 1) * t
  });
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  double x, y, d, t;
  cin >> x >> y >> d >> t;

  double dist = sqrt(x * x + y * y);

  cout << fixed;
  cout.precision(11);
  cout << solve(dist, d, t) << '\n';
}