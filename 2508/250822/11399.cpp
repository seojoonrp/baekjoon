#include <iostream>
#include <algorithm>
using namespace std;

int n;
int arr[1002];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 0; i < n; ++i) cin >> arr[i];
  sort(arr, arr + n);

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    ans += arr[i] * (n - i);
  }

  cout << ans << '\n';
}