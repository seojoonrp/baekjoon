#include <iostream>
using namespace std;

int k;

void merge(int*& a, int p, int q, int r) {
  int* temp = new int[r - p + 1];
  int i = p;
  int j = q + 1;
  int x = 0;

  while (i <= q && j <= r) {
    if (a[i] <= a[j]) temp[x++] = a[i++];
    else temp[x++] = a[j++];
  }

  while (i <= q) {
    temp[x++] = a[i++];
  }
  while (j <= r) {
    temp[x++] = a[j++];
  }

  for (int idx = 0; idx < r - p + 1; ++idx) {
    a[p + idx] = temp[idx];

    k--;
    if (k == 0) cout << temp[idx] << endl;
  }

  delete[] temp;
}

void mergeSort(int*& a, int p, int r) {
  if (p >= r) return;
  
  int q = (p + r) / 2;
  mergeSort(a, p, q);
  mergeSort(a, q + 1, r);
  merge(a, p, q, r);
}

int main() {
  int n;
  cin >> n >> k;

  int* a = new int[n];
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  mergeSort(a, 0, n - 1);

  if (k > 0) cout << "-1" << endl;

  delete[] a;
}