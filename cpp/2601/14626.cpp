#include <iostream>
#include <string>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  string s; cin >> s;

  int n = 0;
  bool is_odd;
  for (int i = 0; i < 13; i++) {
    if (s[i] == '*') {
      is_odd = (i + 1) % 2;
      continue;
    }
    n += (s[i] - '0') * (i % 2 ? 3 : 1);
  }

  if (n % 10 == 0) cout << 0 << '\n';
  else {
    int target = 10 - (n % 10);
    if (is_odd) cout << target << '\n';
    else cout << (target * 7) % 10 << '\n';
  }
}