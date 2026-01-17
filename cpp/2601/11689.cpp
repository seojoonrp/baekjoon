#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
using ll = long long;

const int MAX = 1e6 + 5;

ll n;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  ll temp = n;

  vector<ll> factors;
  for (ll i = 2; i * i <= n; i++) {
    if (temp % i == 0) {
      factors.push_back(i);

      while (temp % i == 0) temp /= i;
    }
  }
  if (temp > 1) factors.push_back(temp);

  for (ll p : factors) {
    n /= p;
    n *= (p - 1);
  }
  cout << n << '\n';
}