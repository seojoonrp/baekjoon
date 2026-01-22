#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

const int N_MAX = 12;
const int C_MAX = 102;

struct Point {
  int x, y;

  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
};

struct State {
  Point rp, bp;
  int depth;

  bool operator==(const State& other) const {
    return rp == other.rp && bp == other.bp;
  }
};

struct StateHash {
  size_t operator()(const State& s) const {
    return (s.rp.x << 15) ^ (s.rp.y << 10) ^ (s.bp.x << 5) ^ s.bp.y;
  }
};

int n, m;
char board[N_MAX][N_MAX];
unordered_map<State, bool, StateHash> visited;
Point hole;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int pidx(Point p) { return p.x * m + p.y; }

State tilt(State cur, int d) {
  int rx = cur.rp.x, ry = cur.rp.y;
  int bx = cur.bp.x, by = cur.bp.y;

  int rdist = 0, bdist = 0;
  while (board[rx + dx[d]][ry + dy[d]] != '#' && board[rx][ry] != 'O') {
    rx += dx[d];
    ry += dy[d];
    rdist++;
  }
  while (board[bx + dx[d]][by + dy[d]] != '#' && board[bx][by] != 'O') {
    bx += dx[d];
    by += dy[d];
    bdist++;
  }

  if (rx == bx && ry == by && !(hole.x == rx && hole.y == ry)) {
    if (rdist > bdist) {
      rx -= dx[d];
      ry -= dy[d];
    } else {
      bx -= dx[d];
      by -= dy[d];
    }
  }

  return {{rx, ry}, {bx, by}, cur.depth + 1};
}

int bfs(State istate) {
  queue<State> q;
  q.push(istate);
  visited.insert({istate, true});

  while (!q.empty()) {
    State cur = q.front();
    q.pop();

    if (cur.depth >= 10) break;

    for (int d = 0; d < 4; d++) {
      State ts = tilt(cur, d);

      if (ts.bp == hole) continue;
      if (ts.rp == hole) return ts.depth;

      if (visited.find(ts) != visited.end()) continue;

      q.push(ts);
      visited.insert({ts, true});
    }
  }

  return -1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;

  State istate;
  for (int i = 1; i <= n; i++) {
    string row; cin >> row;
    for (int j = 1; j <= m; j++) {
      board[i][j] = row[j - 1];

      if (board[i][j] == 'R') istate.rp = {i, j};
      if (board[i][j] == 'B') istate.bp = {i, j};
      if (board[i][j] == 'O') hole = {i, j};
    }
  }

  istate.depth = 0;
  cout << bfs(istate) << '\n';
}