#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

const int MAX = 5e5 + 5;

int n, q;
set<int> s[MAX];

void union_s(int a, int b) {
  if (s[a].size() < s[b].size()) {
    swap(s[a], s[b]); 
  }

  for (int x : s[b]) {
    s[a].insert(x);
  }

  s[b].clear();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> q;

  for (int i = 1; i <= n; i++) {
    int s_size; cin >> s_size;
    while (s_size--) {
      int x; cin >> x;
      s[i].insert(x);
    }
  }

  while (q--) {
    int query; cin >> query;

    if (query == 1) {
      int a, b;
      cin >> a >> b;
      union_s(a, b);
    }

    if (query == 2) {
      int a; cin >> a;
      cout << s[a].size() << '\n';
    }
  }
}