#include <iostream>
#include <deque>
#include <string>
using namespace std;

string s, target;
deque<pair<char, int>> dq;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> s;
  cin >> target;

  for (int i = 0; i < s.length(); ++i) {
    if (dq.empty()) {
      if (s[i] == target[0]) {
        dq.push_back({ s[i], 1 });
        if (target.length() == 1) dq.pop_back();
      }
      else dq.push_back({ s[i], 0 });
    } else {
      auto cur_top = dq.back();

      if (s[i] == target[0]) {
        dq.push_back({ s[i], 1 });
        if (target.length() == 1) dq.pop_back();
      } else if (s[i] == target[cur_top.second]) {
        dq.push_back({ s[i], cur_top.second + 1 });

        if (cur_top.second + 1 == target.length()) {
          for (int x = 0; x < target.length(); ++x) dq.pop_back();
        }
      } else {
        dq.push_back({ s[i], 0 });
      }
    }
  }

  if (dq.empty()) cout << "FRULA\n";
  else {
    while (!dq.empty()) {
      cout << dq.front().first;
      dq.pop_front();
    }
    cout << '\n';
  }
}