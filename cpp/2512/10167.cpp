#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

const int MAX = 3e3 + 5;

struct Node {
  ll sum;
  ll lmax;
  ll rmax;
  ll max;
};

int n;
int x[MAX], y[MAX];
ll w[MAX];
int x_cnt, y_cnt;
int comp_x[MAX], comp_y[MAX];
vector<int> x_idx[MAX], y_idx[MAX];
Node segtree[MAX * 4];

void compress_x() {
  vector<int> vec;
  for (int i = 1; i <= n; i++) vec.push_back(x[i]);
  sort(vec.begin(), vec.end());
  vec.erase(unique(vec.begin(), vec.end()), vec.end());
  x_cnt = vec.size();

  for (int i = 1; i <= n; i++) {
    int idx = lower_bound(vec.begin(), vec.end(), x[i]) - vec.begin() + 1;
    comp_x[i] = idx;
    x_idx[idx].push_back(i);
  }
}
void compress_y() {
  vector<int> vec;
  for (int i = 1; i <= n; i++) vec.push_back(y[i]);
  sort(vec.begin(), vec.end());
  vec.erase(unique(vec.begin(), vec.end()), vec.end());
  y_cnt = vec.size();

  for (int i = 1; i <= n; i++) {
    int idx = lower_bound(vec.begin(), vec.end(), y[i]) - vec.begin() + 1;
    comp_y[i] = idx;
    y_idx[idx].push_back(i);
  }
}

Node merge_node(const Node& l, const Node& r) {
  Node res;
  res.sum = l.sum + r.sum;
  res.lmax = max(l.lmax, l.sum + r.lmax);
  res.rmax = max(r.rmax, r.sum + l.rmax);
  res.max = max({ l.max, r.max, l.rmax + r.lmax });
  return res;
}

void init(int node, int start, int end) {
  if (start == end) {
    segtree[node] = { 0, 0, 0, 0 };
    return;
  }

  int mid = (start + end) / 2;
  init(node * 2, start, mid);
  init(node * 2 + 1, mid + 1, end);

  segtree[node] = { 0, 0, 0, 0 };
}

void update(int node, int start, int end, int idx, ll diff) {
  if (start == end) {
    segtree[node].sum += diff;
    segtree[node].lmax = segtree[node].rmax = segtree[node].max = segtree[node].sum;
    return;
  }

  int mid = (start + end) / 2;
  if (idx <= mid) update(node * 2, start, mid, idx, diff);
  else update(node * 2 + 1, mid + 1, end, idx, diff);

  segtree[node] = merge_node(segtree[node * 2], segtree[node * 2 + 1]);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> x[i] >> y[i] >> w[i];
  }

  compress_x();
  compress_y();

  // 어차피 답은 양수이므로 세그트리, 정답 모두 0으로 초기화해도 됨
  ll ans = 0;

  for (int hi = 1; hi <= y_cnt; hi++) {
    init(1, 1, x_cnt);

    for (int lo = hi; lo >= 1; lo--) {
      for (int g : y_idx[lo]) {
        update(1, 1, x_cnt, comp_x[g], w[g]);
      }
      ans = max(ans, segtree[1].max);
    }
  }

  cout << ans << '\n';
}