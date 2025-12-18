#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> segtree, lazy;
vector<int> init_arr;

void build(int node, int start, int end) {
  if (start == end) {
    segtree[node] = init_arr[start];
    return;
  }

  int mid = (start + end) / 2;
  build(node * 2, start, mid);
  build(node * 2 + 1, mid + 1, end);

  segtree[node] = segtree[node * 2] ^ segtree[node * 2 + 1];
}

void propagate(int node, int start, int end) {
  if (lazy[node] == 0) return;

  int cur_len = end - start + 1;
  if (cur_len % 2 == 1) {
    segtree[node] ^= lazy[node];
  }

  if (start == end) {
    lazy[node] = 0;
    return;
  }

  lazy[node * 2] ^= lazy[node];
  lazy[node * 2 + 1] ^= lazy[node];

  lazy[node] = 0;
}

void update(int node, int start, int end, int left, int right, int diff) {
  propagate(node, start, end);

  if (start > right || end < left) return;

  if (start >= left && end <= right) {
    lazy[node] ^= diff;
    propagate(node, start, end);
    return;
  }

  int mid = (start + end) / 2;
  update(node * 2, start, mid, left, right, diff);
  update(node * 2 + 1, mid + 1, end, left, right, diff);

  segtree[node] = segtree[node * 2] ^ segtree[node * 2 + 1];
}

int query(int node, int start, int end, int left, int right) {
  propagate(node, start, end);

  if (start > right || end < left) return 0; // xor 항등원 = 0

  if (start >= left && end <= right) return segtree[node];

  int mid = (start + end) / 2;
  int query_l = query(node * 2, start, mid, left, right);
  int query_r = query(node * 2 + 1, mid + 1, end, left, right);

  return query_l ^ query_r;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  segtree.resize((n + 1) * 4, 0);
  lazy.resize((n + 1) * 4, 0);
  init_arr.resize(n + 1, 0);

  for (int i = 0; i < n; i++) cin >> init_arr[i];
  build(1, 0, n - 1);

  cin >> m;

  for (int q = 0; q < m; q++) {
    int command;
    cin >> command;

    if (command == 1) {
      int i, j, d;
      cin >> i >> j >> d;
      update(1, 0, n - 1, i, j, d);
    }

    if (command == 2) {
      int i, j;
      cin >> i >> j;
      cout << query(1, 0, n - 1, i, j) << '\n';
    }
  }
}