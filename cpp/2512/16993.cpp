#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 100005;
const int INF = 1e9 + 5;

struct Node {
  int ans_s;
  int ans_m;
  int ans_e;
  int ans_se;
};

int n, m;
int arr[MAX];
Node segtree[MAX * 4];

Node merge(Node& l, Node& r) {
  Node res;
  res.ans_s = max(l.ans_s, l.ans_se + r.ans_s);
  res.ans_e = max(r.ans_e, r.ans_se + l.ans_e);
  res.ans_m = max({l.ans_m, r.ans_m, l.ans_e + r.ans_s});
  res.ans_se = l.ans_se + r.ans_se;
  return res;
}

void build(int node, int start, int end) {
  if (start == end) {
    int a = arr[start];
    segtree[node] = { a, a, a, a };
    return;
  }

  int mid = (start + end) / 2;
  build(node * 2, start, mid);
  build(node * 2 + 1, mid + 1, end);

  Node l = segtree[node * 2];
  Node r = segtree[node * 2 + 1];
  segtree[node] = merge(l, r);
}

Node query(int node, int start, int end, int left, int right) {
  if (start >= left && end <= right) {
    return segtree[node];
  }

  int mid = (start + end) / 2;
  
  if (right <= mid) return query(node * 2, start, mid, left, right);
  if (left > mid) return query(node * 2 + 1, mid + 1, end, left, right);

  Node l = query(node * 2, start, mid, left, right);
  Node r = query(node * 2 + 1, mid + 1, end, left, right);
  return merge(l, r);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> arr[i];

  build(1, 1, n);

  cin >> m;
  while (m--) {
    int i, j;
    cin >> i >> j;

    cout << query(1, 1, n, i, j).ans_m << '\n';
  }
}