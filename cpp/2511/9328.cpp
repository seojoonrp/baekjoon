#include <iostream>
#include <string>
#include <queue>
using namespace std;

const int MAX = 103;
const int ALP = 26;

struct Point {
  int x, y;
};

int n, m;
char board[MAX][MAX];
bool visited[MAX][MAX];
bool key_found[ALP];

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

bool is_lower(const char& c) { return c >= 'a' && c <= 'z'; }
bool is_upper(const char& c) { return c >= 'A' && c <= 'Z'; }

bool is_safe(const int& x, const int& y) {
  if (x < 0 || x > n + 1) return false;
  if (y < 0 || y > m + 1) return false;
  return true;
}

int bfs(int sx, int sy) {
  int ans = 0;

  queue<Point> q;
  q.push({ sx, sy });
  visited[sx][sy] = true;

  queue<Point> door_queue[ALP];

  while (!q.empty()) {
    Point cur = q.front();
    q.pop();

    for (int dir = 0; dir < 4; dir++) {
      int nx = cur.x + dx[dir];
      int ny = cur.y + dy[dir];

      if (!is_safe(nx, ny)) continue;

      char nc = board[nx][ny];
      if (nc == '*' || visited[nx][ny]) continue;

      visited[nx][ny] = true;

      if (is_upper(nc)) {
        if (key_found[nc - 'A']) {
          q.push({ nx, ny });
        } else {
          door_queue[nc - 'A'].push({ nx, ny });
        }
      } else if (is_lower(nc)) {
        q.push({ nx, ny });

        if (!key_found[nc - 'a']) {
          key_found[nc - 'a'] = true;

          while (!door_queue[nc - 'a'].empty()) {
            q.push(door_queue[nc - 'a'].front());
            door_queue[nc - 'a'].pop();
          }
        }
      } else if (nc == '$') {
        q.push({ nx, ny });
        ans++;
      } else {
        q.push({ nx, ny });
      }
    }
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tc;
  cin >> tc;

  while (tc--) {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
      string row;
      cin >> row;
      for (int j = 1; j <= m; j++) {
        board[i][j] = row[j - 1];
      }
    }

    for (int i = 0; i <= n + 1; i++) {
      board[i][0] = '.';
      board[i][m + 1] = '.';
    }
    for (int j = 1; j <= m; j++) {
      board[0][j] = '.';
      board[n + 1][j] = '.';
    }

    string keys;
    cin >> keys;
    if (keys != "0") {
      for (char& c : keys) key_found[c - 'a'] = true;
    }

    cout << bfs(0, 0) << '\n';

    for (int i = 0; i <= n + 1; i++) {
      for (int j = 0; j <= m + 1; j++) {
        board[i][j] = ' ';
        visited[i][j] = false;
      }
    }
    for (int i = 0; i < ALP; i++) {
      key_found[i] = false;
    }
  }
}