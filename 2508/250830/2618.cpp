#include <iostream>
#include <cmath>
#include <climits>
#include <algorithm>
#include <vector>
using namespace std;

struct Point {
  int x, y;
};

int n, w;
Point points[1002];
int dp[1002][1002]; // [경찰차1 인덱스][경찰차2 인덱스]
int where_1[1002], where_2[1002]; // dp[cur][cur - 1]을 계산할 때 경찰차1/2가 어디서 튀어나왔는지

int distance(const int& idx1, const int& idx2, const int& car) {
  Point p1 = points[idx1];
  Point p2 = points[idx2];
  if (idx1 == 0) {
    if (car == 1) p1 = { 1, 1 };
    else p1 = { n, n };
  }
  if (idx2 == 0) {
    if (car == 1) p2 = { 1, 1 };
    else p2 = { n, n };
  }

  return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> w;

  points[0] = { -1, -1 };
  for (int i = 1; i <= w; ++i) cin >> points[i].x >> points[i].y;

  dp[1][0] = distance(0, 1, 1);
  dp[0][1] = distance(0, 1, 2);
  for (int cur = 2; cur <= w; ++cur) {
    for (int i = 0; i < cur - 1; ++i) {
      dp[i][cur] = dp[i][cur - 1] + distance(cur - 1, cur, 2);
      dp[cur][i] = dp[cur - 1][i] + distance(cur - 1, cur, 1);
    }

    int inter_1_min = INT_MAX;
    int inter_2_min = INT_MAX;
    for (int i = 0; i < cur - 1; ++i) {
      if (inter_1_min > dp[i][cur - 1] + distance(i, cur, 1)) {
        inter_1_min = dp[i][cur - 1] + distance(i, cur, 1);
        where_1[cur] = i;
      }
      if (inter_2_min > dp[cur - 1][i] + distance(i, cur, 2)) {
        inter_2_min = dp[cur - 1][i] + distance(i, cur, 2);
        where_2[cur] = i;
      }
    }
    dp[cur][cur - 1] = inter_1_min;
    dp[cur - 1][cur] = inter_2_min;
  }

  int min_dist = INT_MAX;
  int x, y;
  for (int i = 0; i < w; ++i) {
    if (dp[i][w] < min_dist) {
      min_dist = dp[i][w];
      x = i;
      y = w;
    }
    if (dp[w][i] < min_dist) {
      min_dist = dp[w][i];
      x = w;
      y = i;
    }
  }
  cout << min_dist << '\n';

  vector<int> ans;
  while (true) {
    if (x == 1 && y == 0) {
      ans.push_back(1);
      break;
    }
    if (x == 0 && y == 1) {
      ans.push_back(2);
      break;
    }

    if (x < y) {
      ans.push_back(2);
      if (x == y - 1) y = where_2[y];
      else y--;
    } else {
      ans.push_back(1);
      if (y == x - 1) x = where_1[x];
      else x--;
    }
  }

  reverse(ans.begin(), ans.end());
  for (auto& x : ans) cout << x << '\n';
}