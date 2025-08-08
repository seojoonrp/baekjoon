#include <iostream>
#include <algorithm>
#include <climits>
#include <cmath>
using namespace std;

int n;
int arr[100002];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 0; i < n; ++i) cin >> arr[i];

  sort(arr, arr + n);

  int upper = n - 1;
  int lower = 0;
  int cursum = 0;

  int ans_upper = -1;
  int ans_lower = -1;
  int anssum = INT_MAX;

  while (lower < upper) {
    cursum = arr[lower] + arr[upper];
    if (abs(cursum) < anssum) {
      anssum = abs(cursum);
      ans_upper = upper;
      ans_lower = lower;
    }

    if (cursum == 0) {
      break;
    } else if (cursum < 0) {
      lower++;
    } else {
      upper--;
    }
  }

  cout << arr[ans_lower] << " " << arr[ans_upper] << "\n";
}