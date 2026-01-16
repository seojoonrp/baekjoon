#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;

const int MAX = 3e5 + 5;
const ll MOD = 1e9 + 7;

int n;
ll arr[MAX];
ll s[MAX];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
  }

  sort(arr + 1, arr + n + 1);
  for (int i = 1; i <= n; i++) {
    s[i] = (s[i - 1] + arr[i]) % MOD;
  }

  ll ans = 0;
  ll mult_2 = 1;
  for (int k = 2; k <= n; k++) {
    if (k > 2) mult_2 = (mult_2 * 2) % MOD;

    ll calc_s = (s[n] - s[n - k + 1] - s[k - 1]) % MOD;
    ans = (ans + mult_2 * calc_s) % MOD;
  }

  if (ans < 0) ans = (ans + MOD) % MOD;
  cout << ans << '\n';
}