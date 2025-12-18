#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> segtree;
vector<bool> lazy;

void build(int node, int start, int end) {
  if (start == end) {
    segtree[node] = 0;
    return;
  }

  int mid = (start + end) / 2;
  build(node * 2, start, mid);
  build(node * 2 + 1, mid + 1, end);

  segtree[node] = 0;
}

void propagate(int node, int start, int end) {
  if (!lazy[node]) return;

  int cur_len = end - start + 1;
  segtree[node] = cur_len - segtree[node];

  if (start == end) {
    lazy[node] = false;
    return;
  }

  lazy[node * 2] = !lazy[node * 2];
  lazy[node * 2 + 1] = !lazy[node * 2 + 1];

  lazy[node] = 0;
}

void update(int node, int start, int end, int left, int right) {
  propagate(node, start, end);

  if (start > right || end < left) return;

  if (start >= left && end <= right) {
    lazy[node] = !lazy[node];
    propagate(node, start, end);
    return;
  }

  int mid = (start + end) / 2;
  update(node * 2, start, mid, left, right);
  update(node * 2 + 1, mid + 1, end, left, right);

  segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
}

int query(int node, int start, int end, int left, int right) {
  propagate(node, start, end);

  if (start > right || end < left) return 0;

  if (start >= left && end <= right) return segtree[node];

  int mid = (start + end) / 2;
  int query_l = query(node * 2, start, mid, left, right);
  int query_r = query(node * 2 + 1, mid + 1, end, left, right);

  return query_l + query_r;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  segtree.resize((n + 1) * 4, 0);
  lazy.resize((n + 1) * 4, false);

  build(1, 1, n);

  for (int q = 0; q < m; q++) {
    int command;
    cin >> command;

    if (command == 0) {
      int i, j;
      cin >> i >> j;
      update(1, 1, n, i, j);
    }

    if (command == 1) {
      int i, j;
      cin >> i >> j;
      cout << query(1, 1, n, i, j) << '\n';
    }
  }
}