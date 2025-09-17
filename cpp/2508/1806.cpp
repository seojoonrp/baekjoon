#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

int n, s;
int a[100003];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> s;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int upper = 0;
  int lower = 0;
  int ans = INT_MAX;
  int cursum = 0;

  while (lower < n) {
    while (cursum < s && upper < n) {
      cursum += a[upper];
      upper++;
    }

    if (cursum >= s) {
      int tempans = upper - lower;
      ans = min(ans, tempans);
    }

    cursum -= a[lower];
    lower++;
  }

  cout << (ans == INT_MAX ? 0 : ans) << "\n";
}