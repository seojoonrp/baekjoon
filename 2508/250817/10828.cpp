#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n;
  cin >> n;

  stack<int> st;

  while (n--) {
    string command;
    cin >> command;
    
    int x;
    if (command == "push") {
      cin >> x;
      st.push(x);
    } else if (command == "pop") {
      if (st.empty()) cout << "-1\n";
      else {
        cout << st.top() << '\n';
        st.pop();
      }
    } else if (command == "size") {
      cout << st.size() << '\n';
    } else if (command == "empty") {
      cout << st.empty() << '\n';
    } else if (command == "top") {
      if (st.empty()) cout << "-1\n";
      else cout << st.top() << '\n';
    }
  }
}