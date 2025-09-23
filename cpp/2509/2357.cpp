#include <cstdio>
#include <algorithm>
using namespace std;

const int INF = 1e9 + 1;

struct Node {
  int left, right;
  int _min, _max;
};

int n, m;
int arr[100001];
Node tree[400004];

Node init(int left, int right, int index) {
  Node& cur_node = tree[index];
  cur_node.left = left;
  cur_node.right = right;

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

pair<int, int> min_max(int left, int right, int index) {
  Node& cur_node = tree[index];

  if (cur_node.left > right || cur_node.right < left) return { INF, 0 };
  if (cur_node.left >= left && cur_node.right <= right) return { cur_node._min, cur_node._max };

  pair<int, int> child_l = min_max(left, right, index * 2);
  pair<int, int> child_r = min_max(left, right, index * 2 + 1);

  return { min(child_l.first, child_r.first), max(child_l.second, child_r.second) };
}

int main() {
  scanf("%d %d", &n, &m);

  for (int i = 1; i <= n; i++) scanf("%d", &arr[i]);

  init(1, n, 1);

  while (m--) {
    int left, right;
    scanf("%d %d", &left, &right);

    pair<int, int> ans = min_max(left, right, 1);
    printf("%d %d\n", ans.first, ans.second);
  }
}