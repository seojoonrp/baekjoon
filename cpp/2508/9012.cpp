#include <iostream>
#include <string>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n;
  cin >> n;

  while (n--) {
    string s;
    cin >> s;

    int cur = 0;
    bool fucked = false;

    for (int i = 0; i < s.length(); ++i) {
      if (s[i] == '(') cur++;
      else if (s[i] == ')') {
        cur--;
        if (cur < 0) {
          fucked = true;
          break;
        }
      }
    }
    if (cur != 0) fucked = true;

    cout << (fucked ? "NO" : "YES") << '\n';
  }
}