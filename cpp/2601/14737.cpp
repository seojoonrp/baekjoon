#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

const int HW_MAX = 55;
const int NODE_MAX = 2505;

int n, m, nodes;
char board[HW_MAX][HW_MAX];
int node[HW_MAX][HW_MAX];
vector<int> graph[NODE_MAX], graph_r[NODE_MAX];
bool visited[NODE_MAX];
stack<int> stk;

int scc_size;
vector<int> scc[NODE_MAX];
int scc_idx[NODE_MAX];

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

bool is_safe(int x, int y) {
  if (x < 1 || x > n) return false;
  if (y < 1 || y > m) return false;
  return true;
}

void add_edge(int x, int y) {
  for (int d = 0; d < 4; d++) {
    int tx = x, ty = y;
    while (board[tx + dx[d]][ty + dy[d]] != '#' && is_safe(tx + dx[d], ty + dy[d])) {
      tx += dx[d];
      ty += dy[d];
    }
    if (!(tx == x && ty == y)) {
      graph[node[x][y]].push_back(node[tx][ty]);
      graph_r[node[tx][ty]].push_back(node[x][y]);
    }
  }
}

void fill_stack(int cur) {
  visited[cur] = true;
  for (int nxt : graph[cur]) {
    if (!visited[nxt]) fill_stack(nxt);
  }
  stk.push(cur);
}

void rev_dfs(int cur, int scci) {
  visited[cur] = true;
  scc_idx[cur] = scci;
  scc[scci].push_back(cur);

  for (int nxt : graph_r[cur]) {
    if (!visited[nxt]) rev_dfs(nxt, scci);
  }
}

void get_scc() {
  for (int i = 0; i < nodes; i++) {
    if (!visited[i]) fill_stack(i);
  }

  fill(visited, visited + nodes, false);

  while (!stk.empty()) {
    int root = stk.top();
    stk.pop();
    if (!visited[root]) rev_dfs(root, scc_size++);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    string row; cin >> row;
    for (int j = 1; j <= m; j++) {
      board[i][j] = row[j - 1];

      if (board[i][j] != '#') node[i][j] = nodes++;
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (board[i][j] != '#') add_edge(i, j);
    }
  }

  
}