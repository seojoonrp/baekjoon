#include <iostream>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int a, b, v;
  cin >> a >> b >> v;

  if (a == v) cout << 1 << '\n';
  else cout << (v - a - 1) / (a - b) + 2 << '\n';
}