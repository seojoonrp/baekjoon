#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class SegmentTree {
private:
  int n;
  vector<T> tree;
  T identity;

  T merge(T a, T b);

  void build(const vector<T>& data, int node, int start, int end) {
    if (start == end) {
      tree[node] = data[start];
      return;
    }

    int mid = (start + end) / 2;
    build(data, node * 2, start, mid);
    build(data, node * 2 + 1, mid + 1, end);

    tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
  }

  void update(int node, int start, int end, int idx, T val) {
    if (idx < start || idx > end) return;
    if (start == end) {
      tree[node] = val;
      return;
    }

    int mid = (start + end) / 2;
    update(node * 2, start, mid, idx, val);
    update(node * 2 + 1, mid + 1, end, idx, val);

    tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
  }

  T query(int node, int start, int end, int left, int right) {
    if (left > end || right < start) return identity;
    if (left <= start && right >= end) return tree[node];

    int mid = (start + end) / 2;
    T query_l = query(node * 2, start, mid, left, right);
    T query_r = query(node * 2 + 1, mid + 1, end, left, right);

    return merge(query_l, query_r);
  }

public:
  SegmentTree(const vector<T>& data, T identity_val) {
    n = data.size();
    identity = identity_val;

    int tree_size = 4 * n;
    tree.resize(tree_size);

    build(data, 1, 0, n - 1);
  }

  void update(int idx, T val) {
    update(1, 0, n - 1, idx, val);
  }

  T query(int left, int right) {
    return query(1, 0, n - 1, left, right);
  }
};

template <typename T>
T SegmentTree<T>::merge(T a, T b) {
  return a + b;
}