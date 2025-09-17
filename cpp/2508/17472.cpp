#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct bridge {
  int node1, node2;
  int cost;
};

int n, m, ans;
int areaNum = 1;
int board[11][11];
int bridgeGraph[7][7];
int parent[7];
vector<bridge> bridges;

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };
bool visited[11][11];

bool isSafe(int x, int y) {
  if (x < 0 || x >= n) return false;
  if (y < 0 || y >= m) return false;
  return true;
}

void separateArea(int sx, int sy, int target) {
  queue<pair<int, int>> q;
  q.push({ sx, sy });

  while (!q.empty()) {
    pair<int, int> cur = q.front();
    q.pop();
    visited[cur.first][cur.second] = true;
    board[cur.first][cur.second] = target;

    for (int dir = 0; dir < 4; ++dir) {
      int nx = cur.first + dx[dir];
      int ny = cur.second + dy[dir];
      if (isSafe(nx, ny) && board[nx][ny] && !visited[nx][ny]) q.push({ nx, ny });
    }
  }
}

void findBridges() {
  for (int row = 0; row < n; ++row) {
    bool islandFound = false;
    int curIsland = -1;
    int curLength = 0;
    for (int i = 0; i < m; ++i) {
      if (!islandFound && board[row][i]) {
        islandFound = true;
        curIsland = board[row][i];
      }
      if (islandFound) {
        if (board[row][i] == 0) curLength++;
        else if (board[row][i] == curIsland) curLength = 0;
        else {
          int nextIsland = board[row][i];
          int stored = bridgeGraph[curIsland][nextIsland];
          if (curLength >= 2 && (stored == 0 || (stored != 0 && curLength < stored))) {
            bridgeGraph[curIsland][nextIsland] = curLength;
            bridgeGraph[nextIsland][curIsland] = curLength;
          }

          curIsland = nextIsland;
          curLength = 0;
        }
      }
    }
  }
  for (int col = 0; col < m; ++col) {
    bool islandFound = false;
    int curIsland = -1;
    int curLength = 0;
    for (int i = 0; i < n; ++i) {
      if (!islandFound && board[i][col]) {
        islandFound = true;
        curIsland = board[i][col];
      }
      if (islandFound) {
        if (board[i][col] == 0) curLength++;
        else if (board[i][col] == curIsland) curLength = 0;
        else {
          int nextIsland = board[i][col];
          int stored = bridgeGraph[curIsland][nextIsland];
          if (curLength >= 2 && (stored == 0 || (stored != 0 && curLength < stored))) {
            bridgeGraph[curIsland][nextIsland] = curLength;
            bridgeGraph[nextIsland][curIsland] = curLength;
          }

          curIsland = nextIsland;
          curLength = 0;
        }
      }
    }
  }
}

bool compareByCost(const bridge& b1, const bridge& b2) {
  if (b1.cost != b2.cost) return b1.cost < b2.cost;
  if (b1.node1 != b2.node1) return b1.node1 < b2.node1;
  return b1.node2 < b2.node2;
}

int findParent(int node) {
  if (parent[node] == node) return node;

  parent[node] = findParent(parent[node]);
  return parent[node];
}

bool unionNodes(int node1, int node2) {
  int parent1 = findParent(node1);
  int parent2 = findParent(node2);

  if (parent1 == parent2) return true;

  if (parent1 > parent2) parent[parent1] = parent2;
  else parent[parent2] = parent1;

  return false;
}

void mst() {
  sort(bridges.begin(), bridges.end(), compareByCost);
  for (int i = 1; i <= areaNum; ++i) parent[i] = i;

  int connected = 0;
  for (auto& b : bridges) {
    bool isCycle = unionNodes(b.node1, b.node2);
    if (!isCycle) {
      ans += b.cost;
      connected++;
      if (connected == areaNum - 1) break;
    }
  }

  if (connected != areaNum - 1) ans = -1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) cin >> board[i][j];
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (board[i][j] && !visited[i][j]) {
        separateArea(i, j, areaNum);
        areaNum++;
      }
    }
  }
  areaNum--;

  findBridges();

  for (int i = 1; i < areaNum; ++i) {
    for (int j = i + 1; j <= areaNum; ++j) {
      if (bridgeGraph[i][j]) bridges.push_back({ i, j, bridgeGraph[i][j]});
    }
  }

  mst();

  cout << ans << '\n';
}