#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
using m22 = vector<vector<ll>>;

const ll MOD = 1e9 + 7;

ll n;

m22 mult_sqmatrix(int size, const m22& A, const m22& B) {
  m22 res;
  res.resize(size);
  for (int i = 0; i < size; i++) res[i].resize(size, 0);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      for (int k = 0; k < size; k++) {
        ll term = (A[i][k] * B[k][j]) % MOD;
        res[i][j] = (res[i][j] + term) % MOD;
      }
    }
  }

  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;

  if (n % 2 == 1) {
    cout << 0 << '\n';
    return 0;
  }

  m22 res = {{ 1, 0 }, { 0, 1 }};
  m22 multiplier = {{ 3, 1 }, { 2, 1 }};

  ll n2 = n / 2;
  while (n2 > 0) {
    if (n2 % 2 == 1) res = mult_sqmatrix(2, res, multiplier);
    multiplier = mult_sqmatrix(2, multiplier, multiplier);

    n2 /= 2;
  }

  cout << res[0][0] << '\n';
}