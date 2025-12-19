#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 200002;

struct Rect {
  int lo;
  int hi;
};

int n, y_cnt;
Rect rects[MAX];
vector<int> ys;
vector<int> lo_ids[MAX];
vector<int> hi_ids[MAX];
vector<int> segtree, lazy;
vector<int> f;

void compress() {
  sort(ys.begin(), ys.end());
  ys.erase(unique(ys.begin(), ys.end()), ys.end());
  y_cnt = ys.size();

  for (int i = 0; i < n; i++) {
    int lo_id = lower_bound(ys.begin(), ys.end(), rects[i].lo) - ys.begin();
    int hi_id = lower_bound(ys.begin(), ys.end(), rects[i].hi) - ys.begin();

    rects[i].lo = lo_id;
    rects[i].hi = hi_id;

    lo_ids[lo_id].push_back(i);
    hi_ids[hi_id].push_back(i);
  }
}

void calculate_f() {
    f.resize(y_cnt + 1, 0);

    for (int i = 0; i < n; i++) {
        f[rects[i].lo]++;
        f[rects[i].hi + 1]--;
    }

    for (int i = 1; i < y_cnt; i++) {
        f[i] += f[i - 1];
    }
}

void build(int node, int start, int end) {
  if (start == end) {
    segtree[node] = f[start];
    return;
  }

  int mid = (start + end) / 2;
  build(node * 2, start, mid);
  build(node * 2 + 1, mid + 1, end);

  segtree[node] = max(segtree[node * 2], segtree[node * 2 + 1]);
}

void propagate(int node, int start, int end) {
  if (lazy[node] == 0) return;

  segtree[node] += lazy[node];

  if (start == end) {
    lazy[node] = 0;
    return;
  }

  lazy[node * 2] += lazy[node];
  lazy[node * 2 + 1] += lazy[node];

  lazy[node] = 0;
}

void update(int node, int start, int end, int left, int right, int diff) {
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

  segtree[node] = max(segtree[node * 2], segtree[node * 2 + 1]);
}

int query_max() {
  propagate(1, 0, y_cnt - 1);

  return segtree[1];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;

  for (int i = 0; i < n; i++) {
    int x1, x2;
    cin >> x1 >> rects[i].hi >> x2 >> rects[i].lo;
    ys.push_back(rects[i].lo);
    ys.push_back(rects[i].hi);
  }

  compress();
  calculate_f();

  segtree.resize(y_cnt * 4, 0);
  lazy.resize(y_cnt * 4, 0);
  build(1, 0, y_cnt - 1);
  
  int ans = 0;

  for (int i = 0; i < y_cnt; i++) {
    for (int id : lo_ids[i]) {
      update(1, 0, y_cnt - 1, rects[id].lo, rects[id].hi, -1);
    }

    ans = max(ans, f[i] + query_max());

    for (int id : hi_ids[i]) {
      update(1, 0, y_cnt - 1, rects[id].lo, rects[id].hi, 1);
    }
  }

  cout << ans << '\n';
}