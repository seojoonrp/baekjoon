#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int MAX = 100005;

int n, m;
vector<int> childs[MAX];
int in[MAX], out[MAX];
vector<ll> segtree;

int timer = 0;
void dfs(int cur) {
  in[cur] = ++timer;

  for (int c : childs[cur]) {
    dfs(c);
  }

  out[cur] = timer;
}

void update(int node, int start, int end, int idx, int diff) {
  if (idx < start || idx > end) return;

  if (start == end) {
    segtree[node] += diff;
    return;
  }

  int mid = (start + end) / 2;
  update(node * 2, start, mid, idx, diff);
  update(node * 2 + 1, mid + 1, end, idx, diff);

  segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
}

ll query(int node, int start, int end, int left, int right) {
  if (start > right || end < left) return 0;

  if (start >= left && end <= right) return segtree[node];

  int mid = (start + end) / 2;
  ll query_l = query(node * 2, start, mid, left, right);
  ll query_r = query(node * 2 + 1, mid + 1, end, left, right);

  return query_l + query_r;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  segtree.resize((n + 1) * 4, 0);
  
  for (int i = 1; i <= n; i++) {
    int parent;
    cin >> parent;
    if (parent != -1) childs[parent].push_back(i);
  }

  dfs(1);

  while (m--) {
    int command;
    cin >> command;

    if (command == 1) {
      int i; ll w;
      cin >> i >> w;

      update(1, 1, n, in[i], w);
      if (out[i] + 1 <= n) {
        update(1, 1, n, out[i] + 1, -w);
      }
    }
    
    if (command == 2) {
      int i;
      cin >> i;
      cout << query(1, 1, n, 1, in[i]) << '\n';
    }
  }
}