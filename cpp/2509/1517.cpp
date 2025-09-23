#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

struct Node {
  int left, right;
  int _sum;
};

int n, MAX;
int arr[500001];
Node tree[2000004];
ll ans;
vector<int> sorted;

void init(int left, int right, int index) {
  tree[index] = { left, right, 0 };

  if (left == right) return;

  int mid = (left + right) / 2;
  init(left, mid, index * 2);
  init(mid + 1, right, index * 2 + 1);

  return;
}

int interval_sum(int left, int right, int index) {
  Node& cur_node = tree[index];
  if (cur_node.left > right || cur_node.right < left) return 0;
  if (cur_node.left >= left && cur_node.right <= right) return cur_node._sum;

  return interval_sum(left, right, index * 2) + interval_sum(left, right, index * 2 + 1);
}

void update(int targ_index, int delta, int index) {
  Node& cur_node = tree[index];
  if (targ_index < cur_node.left || targ_index > cur_node.right) return;

  cur_node._sum += delta;
  if (cur_node.left == cur_node.right) return;

  update(targ_index, delta, index * 2);
  update(targ_index, delta, index * 2 + 1);
}

int main() {
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
    sorted.push_back(arr[i]);
  }
  sort(sorted.begin(), sorted.end());
  sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());

  for (int i = 0; i < n; i++) {
    arr[i] = lower_bound(sorted.begin(), sorted.end(), arr[i]) - sorted.begin();
    MAX = max(arr[i], MAX);
  }

  init(0, MAX, 1);

  for (int i = 0; i < n; i++) {
    ans += (ll)(interval_sum(arr[i] + 1, MAX, 1));
    update(arr[i], 1, 1);
  }

  printf("%lld\n", ans);
}