#include <iostream>
#include <queue>
using namespace std;

int n, m;
int board[1002][1002];
int visited[1002][1002];

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

bool isSafe(int x, int y) {
  if (x < 0 || x >= n) return false;
  if (y < 0 || y >= m) return false;
  return true;
}

void bfs(int sx, int sy) {
  queue<pair<int, int>> q;

  q.push({ sx, sy });
  visited[sx][sy] = 1;

  while (!q.empty()) {
    pair<int, int> cur = q.front();
    q.pop();

    for (int dir = 0; dir < 4; ++dir) {
      int nx = cur.first + dx[dir];
      int ny = cur.second + dy[dir];

      if (isSafe(nx, ny) && board[nx][ny] && !visited[nx][ny]) {
        q.push({ nx, ny });
        visited[nx][ny] = visited[cur.first][cur.second] + 1;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> m;

  pair<int, int> start;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> board[i][j];
      if (board[i][j] == 2) start = { i, j };
    }
  }

  bfs(start.first, start.second);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (board[i][j] == 0) cout << 0 << ' ';
      else cout << visited[i][j] - 1 << ' ';
    }
    cout << '\n';
  }
}