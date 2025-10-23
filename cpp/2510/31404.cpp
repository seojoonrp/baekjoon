#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAX = 65;

struct Point {
  int x, y;

  Point operator+(const Point& other) const {
    Point res;
    res.x = x + other.x;
    res.y = y + other.y;
    return res;
  }
};

int n, m;
int map_a[MAX][MAX], map_b[MAX][MAX];
bool cleaned[MAX][MAX];
int visited[MAX][MAX][4];
int total, over, clean_count;

Point delta[4] = {{ -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 }};

bool is_safe(const Point& p) {
  if (p.x < 0 || p.x >= n) return false;
  if (p.y < 0 || p.y >= m) return false;
  return true;
}

void clean(const Point& p, int rot) {
  if (!is_safe(p)) {
    return;
  }

  if (!cleaned[p.x][p.y]) {
    cleaned[p.x][p.y] = true;
    clean_count++;
    rot = (rot + map_a[p.x][p.y]) % 4;
    over = 0;
  } else {
    if (visited[p.x][p.y][rot] == clean_count) return;
    visited[p.x][p.y][rot] = clean_count;

    rot = (rot + map_b[p.x][p.y]) % 4;
    over++;
  }

  Point next_p = p + delta[rot];
  total++;
  clean(next_p, rot);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;

  int start_rot;
  Point start_point;
  cin >> start_point.x >> start_point.y >> start_rot;

  string s;
  for (int i = 0; i < n; i++) {
    cin >> s;
    for (int j = 0; j < m; j++) map_a[i][j] = s[j] - '0';
  }
  for (int i = 0; i < n; i++) {
    cin >> s;
    for (int j = 0; j < m; j++) map_b[i][j] = s[j] - '0';
  }

  clean(start_point, start_rot);

  cout << total - over << '\n';
}