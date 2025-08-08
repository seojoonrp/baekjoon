#include <iostream>
#include <stack>
using namespace std;

int main() {
  int n;
  cin >> n;

  stack<int> s;

  for (int i = 0; i < n; ++i) {
    int command;
    cin >> command;

    switch (command) {
    case 1: {
      int num;
      cin >> num;
      s.push(num);
      break;
    }
    case 2: {
      if (s.empty()) cout << "-1\n";
      else {
        cout << s.top() << "\n";
        s.pop();
      }
      break;
    }
    case 3: {
      cout << s.size() << "\n";
      break;
    }
    case 4: {
      cout << (s.empty() ? 1 : 0) << "\n";
      break;
    }
    case 5: {
      if (s.empty()) cout << "-1\n";
      else cout << s.top() << "\n";
      break;
    }
    
    default:
      break;
    }
  }
}