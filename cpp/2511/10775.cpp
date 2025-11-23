#include <iostream>
using namespace std;

const int MAX = 100001;

int g, p;
int parent[MAX];

int find_root(int x) {
  if (parent[x] == x) return x;
  return parent[x] = find_root(parent[x]);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> g >> p;

  for (int i = 0; i <= g; i++) {
    parent[i] = i;
  }

  int ans = 0;
  bool terminated = false;

  for (int i = 1; i <= p; i++) {
    int x;
    cin >> x;

    if (terminated) continue;

    int gate_put = find_root(x);

    if (gate_put == 0) {
      terminated = true;
      continue;
    }

    ans++;

    parent[gate_put] = parent[gate_put - 1];
  }

  cout << ans << '\n';
}