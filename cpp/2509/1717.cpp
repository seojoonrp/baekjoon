#include <iostream>
using namespace std;

int n, m;
int parent[1000001];

int find_parent(int x) {
  if (parent[x] == x) return x;

  return parent[x] = find_parent(parent[x]);
}

void union_nodes(int a, int b) {
  int parent_a = find_parent(a);
  int parent_b = find_parent(b);

  if (parent_a == parent_b) return;

  if (parent_a < parent_b) parent[parent_b] = parent_a;
  else parent[parent_a] = parent_b;
}

bool is_same_set(int a, int b) {
  int parent_a = find_parent(a);
  int parent_b = find_parent(b);

  if (parent_a == parent_b) return true;
  else return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    parent[i] = i;
  }

  while (m--) {
    int command, a, b;
    cin >> command >> a >> b;

    if (command == 0) union_nodes(a, b);
    else {
      cout << (is_same_set(a, b) ? "YES" : "NO") << '\n';
    }
  }
}