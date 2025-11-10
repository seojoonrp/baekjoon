#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAX = 51;
const int C_MAX = 14;
const int INF = 1e9;

struct Chicken {
  int idx;
  int dist;
};

struct Point {
  int x, y;
};

int n, m, h, c;
int board[MAX][MAX];
vector<Point> house_p, chicken_p;
vector<Chicken> houses[MAX * 2];
bool alive[C_MAX];
int ans = INF;

int pdist (Point& p1, Point& p2) {
  return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

bool compare(const Chicken& c1, const Chicken& c2)  {
  return c1.dist < c2.dist;
}

int chicken_dist() {
  int ret = 0;

  for (int i = 0; i < h; i++) {
    for (Chicken& chic : houses[i]) {
      if (alive[chic.idx]) {
        ret += chic.dist;
        break;
      }
    }
  }

  return ret;
}

void solve(int cur, int cnt) {
  if (cnt == m) {
    ans = min(ans, chicken_dist());
    return;
  }

  for (int i = cur + 1; i < c; i++) {
    alive[i] = true;
    solve(i, cnt + 1);
    alive[i] = false;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> board[i][j];
      if (board[i][j] == 1) house_p.push_back({ i, j });
      if (board[i][j] == 2) chicken_p.push_back({ i, j });
    }
  }
  h = (int)house_p.size();
  c = (int)chicken_p.size();

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < c; j++) {
      houses[i].push_back({ j, pdist(house_p[i], chicken_p[j])});
    }
    sort(houses[i].begin(), houses[i].end(), compare);
  }

  solve(-1, 0);

  cout << ans << '\n';
}