#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const double sq2 = sqrt(2) / 2;

struct Point {
  double x, y;
};

double CCW(const Point& a, const Point& b, const Point& c) {
  double ret = 0;
  ret += (a.x * b.y + b.x * c.y + c.x * a.y);
  ret -= (a.y * b.x + b.y * c.x + c.y * a.x);
  return ret;
}

int val[8];
pair<double, double> mult[8] = {
  { 0, 1 },
  { sq2, sq2 },
  { 1, 0 },
  { sq2, -sq2 },
  { 0, -1 },
  { -sq2, -sq2 },
  { -1, 0 },
  { -sq2, sq2 }
};
int ans;
vector<int> indexes;
bool visited[8];

void solve(int x) {
  if (indexes.size() == 8) {
    int flag = 1e9;
    bool fucked = false;

    for (int i = 0; i < 8; ++i) {
      int dir_idx1 = i;
      int dir_idx2 = (i + 1) % 8;
      int dir_idx3 = (i + 2) % 8;
      int val_idx1 = indexes[dir_idx1];
      int val_idx2 = indexes[dir_idx2];
      int val_idx3 = indexes[dir_idx3];

      Point a, b, c;
      a.x = val[val_idx1] * mult[dir_idx1].first;
      a.y = val[val_idx1] * mult[dir_idx1].second;
      b.x = val[val_idx2] * mult[dir_idx2].first;
      b.y = val[val_idx2] * mult[dir_idx2].second;
      c.x = val[val_idx3] * mult[dir_idx3].first;
      c.y = val[val_idx3] * mult[dir_idx3].second;

      double ccw = CCW(a, b, c);
      if (ccw > 0) {
        if (flag == 1e9) flag = 1;
        if (flag != 1) {
          fucked = true;
          break;
        }
      } else if (ccw < 0) {
        if (flag == 1e9) flag = -1;
        if (flag != -1) {
          fucked = true;
          break;
        }
      }
    }

    if (!fucked) ans++;
    return;
  }

  for (int i = 1; i < 8; ++i) {
    if (!visited[i]) {
      visited[i] = true;
      indexes.push_back(i);
      solve(i);
      visited[i] = false;
      indexes.pop_back();
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  for (int i = 0; i < 8; ++i) cin >> val[i];

  visited[0] = true;
  indexes.push_back(0);
  solve(0);

  cout << ans * 8 << '\n';
}