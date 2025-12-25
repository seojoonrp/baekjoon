#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int MAX = 1e5 + 5;
const ll MOD = 1e9 + 7;

int n;
ll arr[MAX];
ll segtree[MAX * 4];
ll prev_dp[MAX];

void init(int node, int start, int end) {
  if (start == end) {
    segtree[node] = 0;
    return;
  }

  int mid = (start + end) / 2;
  init(node * 2, start, mid);
  init(node * 2 + 1, mid + 1, end);

  segtree[node] = 0;
}

void update(int node, int start, int end, int idx, ll diff) {
  if (start > idx || end < idx) return;

  segtree[node] = (segtree[node] + diff) % MOD;
  
  if (start == end) return;

  int mid = (start + end) / 2;
  update(node * 2, start, mid, idx, diff);
  update(node * 2 + 1, mid + 1, end, idx, diff);
}

ll query(int node, int start, int end, int left, int right) {
  if (start > right || end < left) return 0;

  if (start >= left && end <= right) return segtree[node];

  int mid = (start + end) / 2;
  ll query_l = query(node * 2, start, mid, left, right);
  ll query_r = query(node * 2 + 1, mid + 1, end, left, right);

  return (query_l + query_r) % MOD;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> arr[i];

  fill(prev_dp + 1, prev_dp + n + 1, 1);

  for (int k = 2; k <= 11; k++) {
    for (int i = 1; i <= n; i++) {
      update(1, 1, n, arr[i], prev_dp[i]);

      prev_dp[i] = query(1, 1, n, 1, arr[i] - 1);
    }
    init(1, 1, n);
  }

  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    ans = (ans + prev_dp[i]) % MOD;
  }
  cout << ans << '\n';
}