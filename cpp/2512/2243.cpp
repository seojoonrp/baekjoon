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

  void build(int node, int start, int end) {
    if (start == end) {
      tree[node] = 0;
      return;
    }

    int mid = (start + end) / 2;
    build(node * 2, start, mid);
    build(node * 2 + 1, mid + 1, end);

    tree[node] = 0;
  }

  void update(int node, int start, int end, int idx, T val) {
    if (idx > end || idx < start) return;
    if (start == end) {
      tree[node] += val;
      return;
    }

    int mid = (start + end) / 2;
    update(node * 2, start, mid, idx, val);
    update(node * 2 + 1, mid + 1, end, idx, val);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
  }

  int query(int node, int start, int end, T target) {
    if (tree[node] < target) return 0;
    if (start == end) return start;
    
    int mid = (start + end) / 2;
    if (tree[node * 2] >= target) {
      return query(node * 2, start, mid, target);
    } else {
      int new_target = target - tree[node * 2];
      return query(node * 2 + 1, mid + 1, end, new_target);
    }
  }

public:
  SegmentTree(const int node_cnt) {
    n = node_cnt;

    int tree_size = 4 * n;
    tree.resize(tree_size);

    build(1, 0, n - 1);
  }

  void update(int idx, T val) {
    update(1, 0, n - 1, idx, val);
  }

  int query(T target) {
    int ans = query(1, 0, n - 1, target);
    update(ans, -1);
    return ans;
  }
};

const int CANDY = 1000000;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  SegmentTree<int> st(CANDY);

  int n;
  cin >> n;

  while (n--) {
    int command;
    cin >> command;

    if (command == 1) {
      int target;
      cin >> target;
      cout << st.query(target) + 1 << '\n';
    }
    if (command == 2) {
      int idx, val;
      cin >> idx >> val;
      st.update(idx - 1, val);
    }
  }
}