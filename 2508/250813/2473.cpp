#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;

int n;
long arr[5002];

int findClosest(int lower, int upper, long x) {
  int left = lower + 1;
  int right = upper - 1;
  int mid;

  while (left <= right) {
    mid = (left + right) / 2;

    if (arr[mid] == x) return mid;
    else if (arr[mid] > x) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  if (right == lower) return lower + 1;
  else if (left == upper) return upper - 1;
  else {
    return abs(arr[right] - x) < abs(arr[left] - x) ? right : left;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 0; i < n; ++i) cin >> arr[i];

  sort(arr, arr + n);

  long anssum = LONG_MAX;
  int anslower, ansupper, ansmid;

  for (int lower = 0; lower < n - 2; ++lower) {
    for (int upper = lower + 2; upper < n; ++upper) {
      long cursum = arr[lower] + arr[upper];
      
      int mid = findClosest(lower, upper, -cursum);
  
      cursum = abs(cursum + arr[mid]);
      if (cursum < anssum) {
        anssum = cursum;
        anslower = lower;
        ansupper = upper;
        ansmid = mid;
      }
    }
  }

  cout << arr[anslower] << ' ' << arr[ansmid] << ' ' << arr[ansupper] << '\n';
}