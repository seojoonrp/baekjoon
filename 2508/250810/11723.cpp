#include <iostream>
#include <string>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int m;
  cin >> m;

  int S = 0;
  
  while (m--) {
    string command;
    int x;
    cin >> command;


    if (command == "add") {
      cin >> x;
      S |= (1 << x);
    } else if (command == "remove") {
      cin >> x;
      S &= ~(1 << x);
    } else if (command == "check") {
      cin >> x;
      if (S & (1 << x)) cout << 1 << '\n';
      else cout << 0 << '\n';
    } else if (command == "toggle") {
      cin >> x;
      S ^= (1 << x);
    } else if (command == "all") {
      S = (1 << 21) - 2;
    } else if (command == "empty") {
      S = 0;
    }
  }
}