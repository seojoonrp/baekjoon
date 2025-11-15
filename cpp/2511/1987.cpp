#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int MAX = 21;
const int ALPHABET = 27;

struct Point {
  int x, y;
};

int r, c;
int board[MAX][MAX];
bool visited[MAX][MAX];
bool used[ALPHABET];

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

bool is_safe(const Point& p) {
  if (p.x < 0 || p.x >= r) return false;
  if (p.y < 0 || p.y >= c) return false;
  return true;
}

int solve(Point p) {
  int ret = 1;

  for (int d = 0; d < 4; d++) {
    int nx = p.x + dx[d];
    int ny = p.y + dy[d];

    if (is_safe({ nx, ny })) {
      if (!visited[nx][ny] && !used[board[nx][ny]]) {
        visited[nx][ny] = true;
        used[board[nx][ny]] = true;

        ret = max(ret, solve({ nx, ny }) + 1);

        visited[nx][ny] = false;
        used[board[nx][ny]] = false;
      }
    }
  }

  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> r >> c;

  for (int i = 0; i < r; i++) {
    string row;
    cin >> row;
    for (int j = 0; j < c; j++) {
      board[i][j] = row[j] - 'A' + 1;
    }
  }

  visited[0][0] = true;
  used[board[0][0]] = true;
  cout << solve({ 0, 0 }) << '\n';
}