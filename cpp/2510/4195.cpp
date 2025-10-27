#include <iostream>
#include <string>
#include <map>
using namespace std;

const int MAX = 100001;

int n;
map<string, string> parent;
map<string, int> s;

string find_root(const string& name) {
  if (parent[name] == name) return name;
  return parent[name] = find_root(parent[name]);
}

int union_by_size(const string& r1, const string& r2) {
  if (r1 == r2) return s[r1];

  int new_size = s[r1] + s[r2];

  if (s[r1] > s[r2]) {
    parent[r2] = r1;
    s[r1] = new_size;
  } else {
    parent[r1] = r2;
    s[r2] = new_size;
  }

  return new_size;
}

void check_and_insert(const string& name) {
  if (parent.find(name) == parent.end()) {
    parent.insert({ name, name });
    s.insert({ name, 1 });
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tc;
  cin >> tc;

  while (tc--) {
    cin >> n;

    string n1, n2;
    for (int i = 0; i < n; i++) {
      cin >> n1 >> n2;
      
      check_and_insert(n1);
      check_and_insert(n2);

      string r1 = find_root(n1);
      string r2 = find_root(n2);
      cout << union_by_size(r1, r2) << '\n';
    }

    parent.clear();
    s.clear();
  }
}