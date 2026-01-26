#include <iostream>
#include <cmath>
using namespace std;
using ll = long long;

ll x, y;

ll f(ll n) {
  if (n % 2 == 0) return (n * n + 2 * n) / 4;
  return (n * n + 2 * n + 1) / 4;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tc; cin >> tc;
  while (tc--) {
    cin >> x >> y;
    ll target = y - x;

    ll n = sqrt(4 * target) - 1;
    while (f(n) < target) n++;
    cout << n << '\n';
  }
}