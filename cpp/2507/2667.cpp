#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int n;
int graph[27][27];
bool visited[27][27];

vector<int> ans;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

bool isSafe(int x, int y) {
  return (0 <= x && x < n) && (0 <= y && y < n);
}

int bfs(int x, int y) {
  int cnt = 0;
  queue<pair<int, int>> q;

  q.push({x, y});
  visited[x][y] = true;
  cnt++;

  while (!q.empty()) {
    pair<int, int> cur = q.front();
    q.pop();

    for (int dir = 0; dir < 4; ++dir) {
      int nx = cur.first + dx[dir];
      int ny = cur.second + dy[dir];

      if (isSafe(nx, ny) && graph[nx][ny] == 1 && !visited[nx][ny]) {
        q.push({nx, ny});
        visited[nx][ny] = true;
        cnt++;
      }
    }
  }

  return cnt;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < n; ++j) graph[i][j] = s[j] - '0';
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (graph[i][j] == 1 && !visited[i][j]) ans.push_back(bfs(i, j));
    }
  }

  sort(ans.begin(), ans.end());

  cout << ans.size() << "\n";
  for (int i = 0; i < ans.size(); ++i) cout << ans[i] << "\n";
}