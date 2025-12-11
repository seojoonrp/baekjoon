#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

template <typename T>
class SegmentTree {
private:
  int n;
  vector<T> tree;

  void build(const vector<T>& data, int node, int start, int end) {
    if (start == end) {
      tree[node] = data[start];
      return;
    }

    int mid = (start + end) / 2;
    build(data, node * 2, start, mid);
    build(data, node * 2 + 1, mid + 1, end);

    tree[node] = 0;
  }

  void update(int node, int start, int end, int left, int right, T val) {
    if (left > end || right < start) return;
    if (left <= start && right >= end) {
      tree[node] += val;
      return;
    }

    int mid = (start + end) / 2;
    update(node * 2, start, mid, left, right, val);
    update(node * 2 + 1, mid + 1, end, left, right, val);
  }

  T query(int node, int start, int end, int idx) {
    if (start > idx || end < idx) return 0;
    if (start == end) return tree[node];
    
    T ans = tree[node];

    int mid = (start + end) / 2;
    if (idx <= mid) ans += query(node * 2, start, mid, idx);
    else ans += query(node * 2 + 1, mid + 1, end, idx);

    return ans;
  }

public:
  SegmentTree(const vector<T>& data) {
    n = data.size();

    int tree_size = 4 * n;
    tree.resize(tree_size);

    build(data, 1, 0, n - 1);
  }

  void update(int left, int right, T val) {
    update(1, 0, n - 1, left, right, val);
  }

  T query(int idx) {
    return query(1, 0, n - 1, idx);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;

  cin >> n;
  vector<ll> vec(n);
  for (int i = 0; i < n; i++) cin >> vec[i];

  SegmentTree<ll> st(vec);

  cin >> m;
  while (m--) {
    int command;
    cin >> command;

    if (command == 1) {
      int i, j;
      ll k;
      cin >> i >> j >> k;
      st.update(i - 1, j - 1, k);
    } else if (command == 2) {
      int i;
      cin >> i;
      cout << st.query(i - 1) << '\n';
    }
  }
}