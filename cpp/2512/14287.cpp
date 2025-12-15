#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int MAX = 100001;

int n, m;
vector<int> childs[MAX];
int in[MAX], out[MAX];
vector<ll> segtree;

int timer = 0;
void dfs(int cur) {
  in[cur] = ++timer;

  for (int c : childs[cur]) {
    dfs(c);
  }

  out[cur] = timer;
}

void st_update(int node, int start, int end, int idx, ll diff) {
  if (idx < start || idx > end) return;

  if (start == end) {
    segtree[node] += diff;
    return;
  }

  int mid = (start + end) / 2;
  st_update(node * 2, start, mid, idx, diff);
  st_update(node * 2 + 1, mid + 1, end, idx, diff);

  segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
}

ll st_query(int node, int start, int end, int left, int right) {
  if (left > end || right < start) return 0;

  if (left <= start && right >= end) return segtree[node];

  int mid = (start + end) / 2;
  ll query_l = st_query(node * 2, start, mid, left, right);
  ll query_r = st_query(node * 2 + 1, mid + 1, end, left, right);

  return query_l + query_r;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  segtree.resize(4 * (n + 1), 0);

  for (int i = 1; i <= n; i++) {
    int parent;
    cin >> parent;
    if (parent != -1) childs[parent].push_back(i);
  }

  dfs(1);

  while (m--) {
    int command;
    cin >> command;

    if (command == 1) {
      int idx; ll val;
      cin >> idx >> val;
      st_update(1, 1, n, in[idx], val);
    }

    if (command == 2) {
      int idx;
      cin >> idx;
      cout << st_query(1, 1, n, in[idx], out[idx]) << '\n';
    }
  }
}