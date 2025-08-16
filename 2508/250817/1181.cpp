#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

bool compare(const string& a, const string& b) {
  if (a.length() != b.length()) return a.length() < b.length();

  for (int i = 0; i < a.length(); ++i) {
    if (a[i] != b[i]) return a[i] < b[i];
  }

  return false;
}

string arr[20002];

int main() {
  int n;
  cin >> n;

  for (int i = 0; i < n; ++i) cin >> arr[i];

  sort(arr, arr + n, compare);

  for (int i = 0; i < n; ++i) {
    if (i > 0 && arr[i] == arr[i - 1]) continue;
    cout << arr[i] << '\n';
  }
}