#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

struct Point {
  double x;
  double y;
};

int n;
Point points[10002];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;

  for (int i = 0; i < n; ++i) cin >> points[i].x >> points[i].y;

  double ans = 0;

  for (int i = 0; i < n; ++i) {
    int next = (i + 1) % n;

    ans += points[i].x * points[next].y;
    ans -= points[i].y * points[next].x;
  }

  ans /= 2;

  printf("%.1lf", abs(ans));
}