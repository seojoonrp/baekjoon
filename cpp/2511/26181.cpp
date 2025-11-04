#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX = 200001;

struct TreeNode {
  int left, right;
  int parent;
  int lh, rh;

  int lmr() const { return lh - rh; }
  bool is_leaf() const { return left == -1 && right == -1; }
};

struct Result {
  int delete_cnt;
  int height;
};

int n;
TreeNode tree[MAX];
vector<int> link[MAX];
bool visited[MAX];

void init_tree_dfs(int cur, int par) {
  visited[cur] = true;

  TreeNode& t = tree[cur];
  t.parent = par;
  t.left = t.right = -1;

  for (int next : link[cur]) {
    if (next == par) continue;

    if (!visited[next]) {
      if (t.left == -1) t.left = next;
      else t.right = next;

      init_tree_dfs(next, cur);
    }
  }

  if (t.left != -1) t.lh = max(tree[t.left].lh, tree[t.left].rh) + 1;
  else t.lh = -1;
  if (t.right != -1) t.rh = max(tree[t.right].lh, tree[t.right].rh) + 1;
  else t.rh = -1;
}

Result solve(int cur) {
  TreeNode& t = tree[cur];

}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;

  for (int i = 1; i < n; i++) {
    int a, b;
    link[a].push_back(b);
    link[b].push_back(a);
  }

  init_tree_dfs(1, -1);
}