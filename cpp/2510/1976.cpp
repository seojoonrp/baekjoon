#include <iostream>
#include <vector>
using namespace std;

const int MAX = 201;

int n, m;
int parent[MAX], s[MAX];

int find_root(int i) {
  if (parent[i] == i) return i;
  else return parent[i] = find_root(parent[i]);
}

void union_by_size(int r1, int r2) {
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

  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    parent[i] = i;
    s[i] = 1;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int x;
      cin >> x;
      if (j > i) {
        if (x == 1) {
          int ri = find_root(i);
          int rj = find_root(j);
          if (ri != rj) union_by_size(ri, rj);
        }
      }
    }
  }

  int start, start_set;
  cin >> start;
  start_set = find_root(start);

  for (int i = 1; i < m; i++) {
    int x;
    cin >> x;
    if (find_root(x) != start_set) {
      cout << "NO\n";
      return 0;
    }
  }
  cout << "YES\n";
}