#include <iostream>
#include <algorithm>
using namespace std;

int main() {
  int n;
  cin >> n;

  int* a = new int[n];
  int* temp = new int[n];
  bool* checked = new bool[n];

  for (int i = 0; i < n; i++) {
    cin >> a[i];
    temp[i] = a[i];
    checked[i] = false;
  }

  sort(a, a + n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (!checked[j] && a[j] == temp[i]) {
        cout << j << " ";
        checked[j] = true;
        break;
      }
    }
  }

  delete[] a;
  delete[] temp;
  delete[] checked;
}