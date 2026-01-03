#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;

const int MAX = 1e6 + 5;

int n;
ll b, c;
ll arr[MAX];

void edge_case() {
  ll ans = 0;
  for (int i = 1; i <= n; i++) ans += arr[i];
  cout << ans * b << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> b >> c;
  for (int i = 1; i <= n; i++) cin >> arr[i];

  if (b <= c) {
    edge_case();
    return 0;
  }

  ll ans = 0;

  for (int i = 1; i <= n; i++) {
    if (arr[i + 1] > arr[i + 2]) {
      ll two_sel = min(arr[i], arr[i + 1] - arr[i + 2]);
      arr[i] -= two_sel;
      arr[i + 1] -= two_sel;
      ans += two_sel * (b + c);
    }

    ll three_sel = min({ arr[i], arr[i + 1], arr[i + 2] });
    arr[i] -= three_sel;
    arr[i + 1] -= three_sel;
    arr[i + 2] -= three_sel;
    ans += three_sel * (b + 2 * c);

    ans += arr[i] * b;
    arr[i] = 0;
  }

  cout << ans << '\n';
}