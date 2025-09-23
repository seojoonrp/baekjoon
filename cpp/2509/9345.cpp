#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e5;

struct Node {
  int left, right;
  int _min, _max;
};

int n, k;
Node tree[400004];
int arr[100001];
vector<bool> ans;

Node init(int left, int right, int index) {
  Node& cur_node = tree[index];

  cur_node.left = left;
  cur_node.right = right;
  cur_node._min = left;
  cur_node._max = right;

  if (left == right) {
    cur_node._min = arr[left];
    cur_node._max = arr[left];

    return cur_node;
  }

  int mid = (left + right) / 2;
  Node child_l = init(left, mid, index * 2);
  Node child_r = init(mid + 1, right, index * 2 + 1);

  cur_node._min = min(child_l._min, child_r._min);
  cur_node._max = max(child_l._max, child_r._max);

  return cur_node;
}

Node calculate(int left, int right, int index) {
  Node ret = { left, right, INF, 0 };
  Node& cur_node = tree[index];

  if (cur_node.left > right || cur_node.right < left) return ret;
  if (cur_node.left >= left && cur_node.right <= right) return cur_node;

  Node child_l = calculate(left, right, index * 2);
  Node child_r = calculate(left, right, index * 2 + 1);

  ret._min = min(child_l._min, child_r._min);
  ret._max = max(child_l._max, child_r._max);

  return ret;
}

bool check(int left, int right, const Node& calculated) {
  if (calculated._min != left) return false;
  if (calculated._max != right) return false;

  return true;
}

Node update(int target_index, int value, int index) {
  Node& cur_node = tree[index];

  if (target_index < cur_node.left || target_index > cur_node.right) return cur_node;

  if (cur_node.left == cur_node.right) {
    cur_node._min = value;
    cur_node._max = value;

    return cur_node;
  }

  Node child_l = update(target_index, value, index * 2);
  Node child_r = update(target_index, value, index * 2 + 1);

  cur_node._min = min(child_l._min, child_r._min);
  cur_node._max = max(child_l._max, child_r._max);

  return cur_node;
}

int main() {
  int tc;
  scanf("%d", &tc);

  while (tc--) {
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) arr[i] = i;
    init(0, n - 1, 1);

    while (k--) {
      int command, left, right;
      scanf("%d %d %d", &command, &left, &right);

      if (command == 0) {
        update(left, arr[right], 1);
        update(right, arr[left], 1);
        swap(arr[left], arr[right]);
      } else if (command == 1) {
        Node calculated = calculate(left, right, 1);
        ans.push_back(check(left, right, calculated));
      }
    }
  }

  for (bool x : ans) printf("%s\n", x ? "YES" : "NO");
}