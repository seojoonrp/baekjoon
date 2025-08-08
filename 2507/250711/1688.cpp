#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int n;
pair<int, int> point[10002];
double angle[10002];
bool dir; // true = clockwise

const double pi = 3.14159265358979;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n;
  for (int i = 0; i < n; ++i)
  {
    cin >> point[i].first >> point[i].second;
    angle[i] = atan2(point[i].second, point[i].first) * 180 / pi;
    if (angle[i] < 0)
      angle[i] += 360;
  }
}