#include <iostream>
#include <stack>
#include <string>
using namespace std;

stack<char> st;

int precedence(char c) {
  if (c == '*' || c == '/') return 2;
  if (c == '+' || c == '-') return 1;
  if (c == '(') return 0;
  return -1;
}

void handle_operator(char c) {
  if (c == ')') {
    while (st.top() != '(') {
      cout << st.top();
      st.pop();
    }
    st.pop();
  } else {
    int prec = precedence(c);

    if (prec != 0) {
      while (!st.empty() && precedence(st.top()) >= prec) {
        cout << st.top();
        st.pop();
      }
    }

    st.push(c);
  }
}

void handle_char(char c) {
  cout << c;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  string expr;
  cin >> expr;

  for (char c : expr) {
    if (c >= 'A' && c <= 'Z') handle_char(c);
    else handle_operator(c);
  }

  while (!st.empty()) {
    cout << st.top();
    st.pop();
  }

  cout << '\n';
}