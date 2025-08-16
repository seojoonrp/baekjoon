#include <iostream>
using namespace std;

int gcd(int a, int b) {
  if (a < b) return gcd(b, a);
  if (a % b == 0) return b;
  return gcd(b, a % b);
}

int main() {
  int a, b;
  cin >> a >> b;

  cout << gcd(a, b) << '\n';
  cout << (int)(a * b / gcd(a, b)) << '\n';
}