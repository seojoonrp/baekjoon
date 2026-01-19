#include <iostream>
#include <string>
using namespace std;

const int MAX = 1e3 + 5;

int n, m;
int dir[MAX][MAX]; // 0123 = UDLR
int visited[MAX][MAX];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int char_to_dir(char c) {
  if (c == 'U') return 0;
  else if (c == 'D') return 1;
  else if (c == 'L') return 2;
  else return 3;
}

bool is_safe(int x, int y) {
  if (x < 0 || x >= n) return false;
  if (y < 0 || y >= m) return false;
  return true;
}

bool dfs(int x, int y) {
  visited[x][y] = 1;

  int nx = x + dx[dir[x][y]];
  int ny = y + dy[dir[x][y]];
  int nv = visited[nx][ny];

  bool res;
  if (nv == 2) res = true;
  if (nv == 1) res = false;
  if (nv == 0) res = dfs(nx, ny);

  visited[x][y] = 2;
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    string row; cin >> row;
    for (int j = 0; j < m; j++) {
      dir[i][j] = char_to_dir(row[j]);
    }
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (visited[i][j] == 0) {
        bool unified = dfs(i, j);
        if (!unified) ans++;
      }
    }
  }
  cout << ans << '\n';
}