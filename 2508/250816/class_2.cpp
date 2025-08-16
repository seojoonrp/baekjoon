#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n, k;
  cin >> n >> k;

  int ans = 1;
  for (int i = n; i > n - k; --i) ans *= i;
  for (int i = 1; i <= k; ++i) ans /= i;

  cout << ans << '\n';
}