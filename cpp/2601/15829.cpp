#include <iostream>
#include <string>
using namespace std;
using ll = long long;

const ll R = 31;
const ll MOD = 1234567891;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  string s;
  cin >> n >> s;

  ll ans = 0;
  for (int i = n - 1; i >= 0; i--) {
    ans = (ans * R) % MOD;
    ans = (ans + (s[i] - 'a' + 1)) % MOD;
  }

  cout << ans << '\n';
}