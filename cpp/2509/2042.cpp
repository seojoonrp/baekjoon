#include <cstdio>
using namespace std;
using ll = long long;

struct Node {
  ll value;
  int left;
  int right;
};

int n, m, k;
ll arr[1000001];
Node tree[4000004];

Node init(int left, int right, int index) {
  Node& ret = tree[index];
  ret.left = left;
  ret.right = right;

  if (left == right) {
    ret.value = arr[left];
    return ret;
  }

  int mid = (left + right) / 2;
  ret.value = init(left, mid, index * 2).value + init(mid + 1, right, index * 2 + 1).value;
  
  return ret;
}

ll interval_sum(int left, int right, int index) {
  Node& cur_node = tree[index];
  if (cur_node.left > right || cur_node.right < left) return 0;
  if (cur_node.left >= left && cur_node.right <= right) return cur_node.value;

  return interval_sum(left, right, index * 2) + interval_sum(left, right, index * 2 + 1);
}

void update(int index, int targ_index, ll delta) {
  Node& cur_node = tree[index];
  if (targ_index < cur_node.left || targ_index > cur_node.right) return;

  cur_node.value += delta;
  if (cur_node.left == cur_node.right) return;

  update(index * 2, targ_index, delta);
  update(index * 2 + 1, targ_index, delta);
}

int main() {
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 1; i <= n; i++) scanf("%lld", &arr[i]);

  init(1, n, 1);

  for (int i = 0; i < m + k; i++) {
    int command;
    scanf("%d", &command);

    if (command == 1) {
      int index;
      ll num;
      scanf("%d %lld", &index, &num);
      ll delta = num - arr[index];

      arr[index] = num;
      update(1, index, delta);
    } else if (command == 2) {
      int left, right;
      scanf("%d %d", &left, &right);
      printf("%lld\n", interval_sum(left, right, 1));
    }
  }
}