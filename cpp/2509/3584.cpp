#include <cstdio>
#include <vector>
using namespace std;

int n, root, a, b;
int parent[10001];
vector<int> tree[10001];
vector<int> a_path, b_path;
vector<int> ans;

void find_path(int node, vector<int>& cur_path) {
  cur_path.push_back(node);

  if (node == a) a_path = cur_path;
  if (node == b) b_path = cur_path;

  for (int next : tree[node]) {
    find_path(next, cur_path);
  }

  cur_path.pop_back();
}

int main() {
  int tc;
  scanf("%d", &tc);

  while (tc--) {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) parent[i] = i;

    for (int i = 1; i < n; i++) {
      int p, c;
      scanf("%d %d",&p, &c);
      tree[p].push_back(c);
      parent[c] = p;
    }

    scanf("%d %d", &a, &b);

    for (int i = 1; i <= n; i++) {
      if (parent[i] == i) {
        root = i;
        break;
      }
    }

    vector<int> path;
    find_path(root, path);

    size_t idx = 0;
    int cur_ans = root;

    while (idx < a_path.size() && idx < b_path.size()) {
      if (a_path[idx] != b_path[idx]) break;

      cur_ans = a_path[idx];
      idx++;
    }

    ans.push_back(cur_ans);

    for (int i = 1; i <= n; i++) tree[i].clear();
  }

  for (int x : ans) printf("%d\n", x);
}