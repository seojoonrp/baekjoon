#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX = 5e5 + 3;

int n, k, d;
int arr[MAX];
vector<int> segtree;
int mod_max_dp[MAX];

void update(int node, int start, int end, int idx, int val) {
  if (start > idx || end < idx) return;
  
  if (start == end) {
    segtree[node] = max(segtree[node], val);
    return;
  }

  int mid = (start + end) / 2;
  update(node * 2, start, mid, idx, val);
  update(node * 2 + 1, mid + 1, end, idx, val);

  segtree[node] = max(segtree[node * 2], segtree[node * 2 + 1]);
}

int query(int node, int start, int end, int left, int right) {
  if (start > right || end < left) return 0;

  if (start >= left && end <= right) return segtree[node];

  int mid = (start + end) / 2;
  int query_l = query(node * 2, start, mid, left, right);
  int query_r = query(node * 2 + 1, mid + 1, end, left, right);

  return max(query_l, query_r);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> k >> d;

  int arr_max = -1;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
    arr_max = max(arr_max, arr[i]);
  }
  segtree.resize((arr_max + 1) * 4, 0);

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int lo = max(1, arr[i] - d);
    int hi = min(arr_max, arr[i] + d);
    int dp = query(1, 1, arr_max, lo, hi);

    int mod_i = arr[i] % k;
    dp = max(dp, mod_max_dp[mod_i]);

    int cur_ans = dp + 1;

    update(1, 1, arr_max, arr[i], cur_ans);
    mod_max_dp[mod_i] = max(mod_max_dp[mod_i], cur_ans);

    ans = max(ans, cur_ans);
  }

  cout << ans << '\n';
}