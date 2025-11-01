#include <iostream>
using namespace std;

const int MAX = 500001;

int parent[MAX];
int s[MAX];

int find_root(int node) {
  if (parent[node] == node) return node;
  return parent[node] = find_root(parent[node]);
}

void union_root(int r1, int r2) {
  int new_size = s[r1] + s[r2];

  if (s[r1] > s[r2]) {
    parent[r2] = r1;
    s[r1] = new_size;
  } else {
    parent[r1] = r2;
    s[r2] = new_size;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    parent[i] = i;
    s[i] = 1;
  }

  int ans = 0;

  for (int i = 1; i <= m; i++) {
    int a, b;
    cin >> a >> b;

    if (ans != 0) continue;

    int r1 = find_root(a);
    int r2 = find_root(b);
    if (r1 == r2) {
      ans = i;
      continue;
    } else {
      union_root(r1, r2);
    }
  }

  cout << ans << '\n';
}