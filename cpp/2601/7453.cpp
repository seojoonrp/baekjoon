#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;

const int MAX = 4e3 + 5;

int n;
int a[MAX], b[MAX], c[MAX], d[MAX];
vector<int> absum;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> b[i] >> c[i] >> d[i];
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) absum.push_back(a[i] + b[j]);
  }
  sort(absum.begin(), absum.end());

  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int target = c[i] + d[j];
      auto lb = lower_bound(absum.begin(), absum.end(), -target);
      auto ub = upper_bound(absum.begin(), absum.end(), -target);
      ans += ub - lb;
    }
  }
  cout << ans << '\n';
}