#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 1e5 + 5;
const int INF = 1e9 + 5;

struct Node {
  int val;
  int idx;
};

int n, m;
int arr[MAX];
vector<Node> segtree;

void merge(int node) {
  Node cl = segtree[node * 2];
  Node cr = segtree[node * 2 + 1];
  if (cl.val <= cr.val) segtree[node] = cl;
  else segtree[node] = cr;
}

void build(int node, int start, int end) {
  if (start == end) {
    segtree[node].val = arr[start];
    segtree[node].idx = start;
    return;
  }

  int mid = (start + end) / 2;
  build(node * 2, start, mid);
  build(node * 2 + 1, mid + 1, end);

  merge(node);
}

void update(int node, int start, int end, int idx, int val) {
  if (idx < start || idx > end) return;

  if (start == end) {
    segtree[node].val = val;
    return;
  }

  int mid = (start + end) / 2;
  update(node * 2, start, mid, idx, val);
  update(node * 2 + 1, mid + 1, end, idx, val);

  merge(node);
}

Node query(int node, int start, int end, int left, int right) {
  if (end < left || start > right) return { INF, -1 };

  if (start >= left && end <= right) return segtree[node];

  int mid = (start + end) / 2;
  Node ql = query(node * 2, start, mid, left, right);
  Node qr = query(node * 2 + 1, mid + 1, end, left, right);

  return ql.val <= qr.val ? ql : qr;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> arr[i];

  segtree.resize((n + 1) * 4);
  build(1, 1, n);

  cin >> m;
  while (m--) {
    int command; cin >> command;

    if (command == 1) {
      int i, v; cin >> i >> v;
      update(1, 1, n, i, v);
    }

    if (command == 2) {
      int i, j; cin >> i >> j;
      cout << query(1, 1, n, i, j).idx << '\n';
    }
  }
}