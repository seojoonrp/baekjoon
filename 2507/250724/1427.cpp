#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int n;
int a[12];

int partition(int left, int right) {
  int pivot = a[left];
  int low = left + 1;
  int high = right;

  while (low <= high) {
    while (low <= right && a[low] > pivot) low++;
    while (high >= left + 1 && a[high] < pivot) high--;

    if (low <= high) {
      swap(a[low], a[high]);
      low++;
      high--;
    }
  }

  swap(a[left], a[high]);
  return high;
}

void quickSort(int left, int right) {
  if (left >= right) return;

  int q = partition(left, right);

  quickSort(left, q - 1);
  quickSort(q + 1, right);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;

  int idx = 0;
  while (n > 0) {
    a[idx++] = n % 10;
    n /= 10;
  }

  quickSort(0, idx - 1);

  for (int i = 0; i < idx; ++i) cout << a[i];
  cout << "\n";
}