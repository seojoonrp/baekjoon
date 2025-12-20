#include <iostream>
#include <vector>
using namespace std;

const int N_MAX = 100000;
const int K_MAX = 10;
const int MOD = 1e9 + 7;

int n, k;
int arr[N_MAX + 1];
int dp[K_MAX + 1][N_MAX + 1]; // dp[i][j] = j번 인덱스에서 끝나는 길이 i인 증가수열의 개수

vector<int> segtree;

void init_tree(int node, int start, int end) {
  if (start == end) {
    segtree[node] = 0;
    return;
  }

  int mid = (start + end) / 2;
  init_tree(node * 2, start, mid);
  init_tree(node * 2 + 1, mid + 1, end);

  segtree[node] = 0;
}

void update(int node, int start, int end, int idx, int diff) {
  if (start > idx || end < idx) return;

  segtree[node] = (segtree[node] + diff) % MOD;
  
  if (start == end) return;

  int mid = (start + end) / 2;
  update(node * 2, start, mid, idx, diff);
  update(node * 2 + 1, mid + 1, end, idx, diff);
}

int query(int node, int start, int end, int left, int right) {
  if (start > right || end < left) return 0;

  if (start >= left && end <= right) return segtree[node];

  int mid = (start + end) / 2;
  int query_l = query(node * 2, start, mid, left, right);
  int query_r = query(node * 2 + 1, mid + 1, end, left, right);

  return (query_l + query_r) % MOD;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> k;
  for (int i = 1; i <= n; i++) cin >> arr[i];

  segtree.resize((N_MAX + 1) * 4, 0);
  init_tree(1, 1, n);

  for (int j = 1; j <= n; j++) dp[1][j] = 1;

  for (int i = 2; i <= k; i++) {
    for (int j = 1; j <= n; j++) {
      update(1, 1, n, arr[j], dp[i - 1][j]);
      dp[i][j] = query(1, 1, n, 1, arr[j] - 1);
    }

    init_tree(1, 1, n);
  }

  int ans = 0;
  for (int j = 1; j <= n; j++) {
    ans = (ans + dp[k][j]) % MOD;
  }
  cout << ans << '\n';
}