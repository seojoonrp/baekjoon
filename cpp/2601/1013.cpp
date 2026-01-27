#include <iostream>
#include <string>
using namespace std;

struct State {
  int zero;
  int one;
  bool ok;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  State states[9];
  states[0] = {1, 2, true};
  states[1] = {8, 0, false};
  states[2] = {3, 8, false};
  states[3] = {4, 8, false};
  states[4] = {4, 5, false};
  states[5] = {1, 6, true};
  states[6] = {7, 6, true};
  states[7] = {4, 0, false};
  states[8] = {8, 8, false};

  int tc; cin >> tc;
  while (tc--) {
    string s; cin >> s;

    State cur = states[0];
    for (char c : s) {
      if (c == '0') cur = states[cur.zero];
      else cur = states[cur.one];
    }

    if (cur.ok) cout << "YES" << '\n';
    else cout << "NO" << '\n';
  }
}