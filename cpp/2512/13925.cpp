#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int MAX = 1e5 + 5;
const ll MOD = 1e9 + 7;

struct Lazy {
  ll a, b; // y = ax + b
};

int n, m;
ll arr[MAX];
ll segtree[MAX * 4];
Lazy lazy[MAX * 4];

void build(int node, int start, int end) {
  if (start == end) {
    segtree[node] = arr[start];
    lazy[node] = { 1, 0 };
    return;
  }

  int mid = (start + end) / 2;
  build(node * 2, start, mid);
  build(node * 2 + 1, mid + 1, end);

  segtree[node] = (segtree[node * 2] + segtree[node * 2 + 1]) % MOD;
  lazy[node] = { 1, 0 };
}

Lazy calc_lazy(Lazy& l1, Lazy& l2) {
  Lazy res;
  res.a = (l1.a * l2.a) % MOD;
  res.b = (l1.b * l2.a + l2.b) % MOD;
  return res;
}

void propagate(int node, int start, int end) {
  if (lazy[node].a == 1 && lazy[node].b == 0) return;

  segtree[node] = (lazy[node].a * segtree[node]) % MOD;
  segtree[node] = (lazy[node].b * (end - start + 1) + segtree[node]) % MOD;

  if (start == end) {
    lazy[node] = { 1, 0 };
    return;
  }

  lazy[node * 2] = calc_lazy(lazy[node * 2], lazy[node]);
  lazy[node * 2 + 1] = calc_lazy(lazy[node * 2 + 1], lazy[node]);

  lazy[node] = { 1, 0 };
}

void update_plus(int node, int start, int end, int left, int right, ll diff) {
  propagate(node, start, end);

  if (start > right || end < left) return;

  if (start >= left && end <= right) {
    lazy[node].b = (diff + lazy[node].b) % MOD;
    propagate(node, start, end);
    return;
  }

  int mid = (start + end) / 2;
  update_plus(node * 2, start, mid, left, right, diff);
  update_plus(node * 2 + 1, mid + 1, end, left, right, diff);

  segtree[node] = (segtree[node * 2] + segtree[node * 2 + 1]) % MOD;
}

void update_mult(int node, int start, int end, int left, int right, ll mult) {
  propagate(node, start, end);

  if (start > right || end < left) return;

  if (start >= left && end <= right) {
    lazy[node].a = (mult * lazy[node].a) % MOD;
    lazy[node].b = (mult * lazy[node].b) % MOD;
    propagate(node, start, end);
    return;
  }

  int mid = (start + end) / 2;
  update_mult(node * 2, start, mid, left, right, mult);
  update_mult(node * 2 + 1, mid + 1, end, left, right, mult);

  segtree[node] = (segtree[node * 2] + segtree[node * 2 + 1]) % MOD;
}

void update_change(int node, int start, int end, int left, int right, ll val) {
  propagate(node, start, end);

  if (start > right || end < left) return;

  if (start >= left && end <= right) {
    lazy[node].a = 0;
    lazy[node].b = val;
    propagate(node, start, end);
    return;
  }

  int mid = (start + end) / 2;
  update_change(node * 2, start, mid, left, right, val);
  update_change(node * 2 + 1, mid + 1, end, left, right, val);

  segtree[node] = (segtree[node * 2] + segtree[node * 2 + 1]) % MOD;
}

ll query_sum(int node, int start, int end, int left, int right) {
  propagate(node, start, end);

  if (start > right || end < left) return 0;

  if (start >= left && end <= right) return segtree[node];

  int mid = (start + end) / 2;
  ll query_l = query_sum(node * 2, start, mid, left, right);
  ll query_r = query_sum(node * 2 + 1, mid + 1, end, left, right);

  return (query_l + query_r) % MOD;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> arr[i];

  build(1, 1, n);

  cin >> m;
  while (m--) {
    int command;
    cin >> command;
    int x, y; ll v;

    if (command == 1) {
      cin >> x >> y >> v;
      update_plus(1, 1, n, x, y, v);
    }

    if (command == 2) {
      cin >> x >> y >> v;
      update_mult(1, 1, n, x, y, v);
    }

    if (command == 3) {
      cin >> x >> y >> v;
      update_change(1, 1, n, x, y, v);
    }

    if (command == 4) {
      cin >> x >> y;
      cout << query_sum(1, 1, n, x, y) << '\n';
    }
  }
}