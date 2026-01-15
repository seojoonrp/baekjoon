#include <iostream>
#include <string>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int num = -1;
  for (int i = 0; i < 3; i++) {
    string s; cin >> s;
    if (s[0] != 'F' && s[0] != 'B') {
      int sn = stoi(s);
      num = sn + (3 - i);
    }
  }

  if (num % 3 == 0 && num % 5 == 0) {
    cout << "FizzBuzz" << '\n';
  } else if (num % 3 == 0) {
    cout << "Fizz" << '\n';
  } else if (num % 5 == 0) {
    cout << "Buzz" << '\n';
  } else {
    cout << num << '\n';
  }
}