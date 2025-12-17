#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int n, m, k;
vector<ll> segtree, lazy;
vector<ll> init_arr;

void build(int node, int start, int end) {
  if (start == end) {
    segtree[node] = init_arr[start];
    return;
  }

  int mid = (start + end) / 2;
  build(node * 2, start, mid);
  build(node * 2 + 1, mid + 1, end);

  segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
}

void propagate(int node, int start, int end) {
  if (lazy[node] == 0) return;

  ll diff_val = lazy[node] * (ll)(end - start + 1);
  segtree[node] += diff_val;

  if (start == end) {
    lazy[node] = 0;
    return;
  }

  lazy[node * 2] += lazy[node];
  lazy[node * 2 + 1] += lazy[node];

  lazy[node] = 0;
}

void update(int node, int start, int end, int left, int right, ll diff) {
  propagate(node, start, end);

  if (start > right || end < left) return;

  if (start >= left && end <= right) {
    lazy[node] += diff;
    propagate(node, start, end);
    return;
  }

  int mid = (start + end) / 2;
  update(node * 2, start, mid, left, right, diff);
  update(node * 2 + 1, mid + 1, end, left, right, diff);

  segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
}

ll query(int node, int start, int end, int left, int right) {
  propagate(node, start, end);

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

  cin >> n >> m >> k;
  segtree.resize((n + 1) * 4, 0);
  lazy.resize((n + 1) * 4, 0);
  init_arr.resize(n + 1, 0);

  for (int i = 1; i <= n; i++) cin >> init_arr[i];
  build(1, 1, n);

  for (int q = 0; q < m + k; q++) {
    int command;
    cin >> command;

    if (command == 1) {
      int i, j; ll d;
      cin >> i >> j >> d;
      update(1, 1, n, i, j, d);
    }

    if (command == 2) {
      int i, j;
      cin >> i >> j;
      cout << query(1, 1, n, i, j) << '\n';
    }
  }
}