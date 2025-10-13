#include <iostream>
#include <array>
using namespace std;
using ll = long long;

typedef array<array<ll, 2>, 2> m22;

const ll MOD = 1000000007;

m22 multiply_matrix(const m22& A, const m22& B) {
  m22 result = {{{{ 0, 0 }}, {{ 0, 0 }}}};

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        ll term = (A[i][k] * B[k][j]) % MOD;
        result[i][j] = (result[i][j] + term) % MOD;
      }
    }
  }

  return result;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n;
  cin >> n;

  if (n == 0) cout << "0\n";
  else {
    m22 result = {{{{ 1, 0 }}, {{ 0, 1 }}}};
    m22 multiplier = {{{{ 1, 1 }}, {{ 1, 0 }}}};

    while (n > 0) {
      if (n % 2 == 1) result = multiply_matrix(result, multiplier);
      multiplier = multiply_matrix(multiplier, multiplier);

      n /= 2;
    }

    cout << result[1][0] << '\n';
  }
}