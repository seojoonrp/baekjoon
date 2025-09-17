#include <iostream>
#include <queue>
using namespace std;

int n, m;
int board[52][52];
bool visited[52][52];

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

bool isSafe(int x, int y) {
  if (x < 0 || x >= n) return false;
  if (y < 0 || y >= m) return false;
  return true;
}

void bfs(int x, int y) {
  queue<pair<int ,int>> q;
  q.push({ x, y });
  visited[x][y] = true;

  while (!q.empty()) {
    pair<int, int> cur = q.front();
    q.pop();

    for (int dir = 0; dir < 4; ++dir) {
      int nx = cur.first + dx[dir];
      int ny = cur.second + dy[dir];
      if (isSafe(nx, ny) && board[nx][ny] && !visited[nx][ny]) {
        visited[nx][ny] = true;
        q.push({ nx, ny });
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int tc;
  cin >> tc;

  while (tc--) {
    int k;
    cin >> n >> m >> k;

    while (k--) {
      int x, y;
      cin >> x >> y;
      board[x][y] = 1;
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (board[i][j] && !visited[i][j]) {
          bfs(i, j);
          ans++;
        }
      }
    }

    cout << ans << '\n';

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        board[i][j] = 0;
        visited[i][j] = false;
      }
    }
  }
}