#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 5000000;

int n, k;
int arr[MAX];

void insertion_sort(const int& left, const int& right) {
  for (int i = left + 1; i < right; i++) {
    for (int j = i; j > left; j--) {
      if (arr[j - 1] > arr[j]) {
        swap(arr[j - 1], arr[j]);
      } else {
        break;
      }
    }
  }
}

int select_pivot(const int& left, const int& right) {
  int mid = (left + right) / 2;
  int last = right - 1;

  if (arr[left] > arr[mid]) swap(arr[left], arr[mid]);
  if (arr[left] > arr[last]) swap(arr[left], arr[last]);
  if (arr[mid] > arr[last]) swap(arr[mid], arr[last]);

  swap(arr[mid], arr[last]);
  return arr[last];
}

void quick_sort(const int& left, const int& right) {
  if (right - left <= 6) {
    insertion_sort(left, right);
    return;
  }

  int pivot = select_pivot(left, right);
  int lo = left;
  int hi = right - 2;
  
  while (true) {
    while (arr[lo] < pivot) { lo++; }
    while (hi > left && arr[hi] > pivot) { hi--; }

    if (lo < hi) {
      swap(arr[lo], arr[hi]);
      lo++; hi--;
    }
    else break;
  }

  swap(arr[lo], arr[right - 1]);

  quick_sort(left, lo);
  quick_sort(lo + 1, right);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> arr[i];

  quick_sort(0, n);

  cout << arr[k - 1] << '\n';
}