#include <iostream>
#include <algorithm>
using namespace std;

int n, x;
int a[100002];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i];
  cin >> x;

  sort(a, a + n);

  int start = 0;
  int end = n - 1;
  int ans = 0;

  while (start < end) {
    int cursum = a[start] + a[end];

    if (cursum == x) {
      ans++;
      start++;
      end--;
    } else if (cursum > x) {
      end--;
    } else {
      start++;
    }
  }

  cout << ans << "\n";
}