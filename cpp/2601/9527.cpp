#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

ll a, b;

vector<int> bin(ll n) {
  vector<int> res;
  while (n > 0) {
    res.push_back(n % 2);
    n /= 2;
  }
  return res;
}

ll solve(ll n) {
  vector<int> b = bin(n);

  ll res = 0;
  ll cur = 0;
  ll mult2 = 1;

  for (int i = 0; i < (int)b.size(); i++) {
    if (b[i] == 1) {
      if (i == 0) res += 1;
      else {
        res += (mult2 / 2) * i;
        res += cur + 1;
      }

      cur += mult2;
    }

    mult2 *= 2;
  }

  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> a >> b;
  cout << solve(b) - solve(a - 1) << '\n';
}