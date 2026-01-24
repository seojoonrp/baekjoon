#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tc; cin >> tc;
  while (tc--) {
    string f;
    int n;
    deque<int> dq;

    cin >> f >> n;

    char dummy;
    int x;
    cin >> dummy;
    if (n > 0) {
      for (int i = 0; i < n; i++) {
        cin >> x >> dummy;
        dq.push_back(x);
      }
    } else {
      cin >> dummy;
    }

    bool rev = false;
    bool error = false;
    for (char c : f) {
      if (c == 'R') {
        rev = !rev;
      } else {
        if (dq.empty()) {
          error = true;
          break;
        }

        if (rev) dq.pop_back();
        else dq.pop_front();
      }
    }
    if (rev) reverse(dq.begin(), dq.end());

    if (error) cout << "error" << '\n';
    else {
      if (dq.empty()) cout << "[]";
      else {
        cout << '[';
        for (int i = 0; i < (int)dq.size(); i++) {
          cout << dq[i];
          if (i < (int)dq.size() - 1) cout << ',';
          else cout << ']';
        }
      }
      cout << '\n';
    }
  }
}