#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;

int a[100002];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i];

  sort(a, a + n);

  int start = 0;
  int end = n - 1;
  int cursum = 0;
  pair<int, int> ans = {0, n - 1};
  int anssum = INT_MAX;

  while (start < end) {
    cursum = a[start] + a[end];
    
    if (abs(cursum) < anssum) {
      anssum = abs(cursum);
      ans = {start, end};
    }

    if (cursum < 0) {
      start++;
    } else {
      end--;
    }
  }

  cout << a[ans.first] << " " << a[ans.second] << "\n";
}