#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int MAX = 2e5 + 5;

int n, c, q;
vector<int> graph[MAX];
int depth[MAX];
int in[MAX], out[MAX];
ll segtree[MAX * 4];

int timer = 1;
void dfs(int cur, int d) {
  depth[cur] = d;
  in[cur] = timer++;

  for (int child : graph[cur]) {
    if (depth[child] == 0) {
      dfs(child, d + 1);
    }
  }

  out[cur] = timer;
}

void update(int node, int start, int end, int idx, ll diff) {
  if (idx < start || idx > end) return;

  if (start == end) {
    segtree[node] += diff;
    return;
  }

  int mid = (start + end) / 2;
  update(node * 2, start, mid, idx, diff);
  update(node * 2 + 1, mid + 1, end, idx, diff);

  segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
}

ll query(int node, int start, int end, int left, int right) {
  if (start > right || end < left) return 0;

  if (start >= left && end <= right) return segtree[node];

  int mid = (start + end) / 2;
  ll query_l = query(node * 2, start, mid, left, right);
  ll query_r = query(node * 2 + 1, mid + 1, end, left, right);

  return query_l + query_r;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> c;

  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  dfs(c, 1);

  cin >> q;
  while (q--) {
    int command, idx;
    cin >> command >> idx;

    if (command == 1) {
      update(1, 1, n, in[idx], 1);
    }

    if (command == 2) {
      ll water_cnt = query(1, 1, n, in[idx], out[idx] - 1);
      cout << water_cnt * (ll)depth[idx] << '\n';
    }
  }
}