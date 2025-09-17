#include <iostream>
#include <string>
#include <math.h>
using namespace std;

void cantor(string& a, int start, int n) {
  if (n == 0) return;

  int segment = 1;
  for (int i = 0; i < n - 1; ++i) segment *= 3;

  for (int i = start + segment; i < start + segment * 2; ++i) a[i] = ' ';

  cantor(a, start, n - 1);
  cantor(a, start + segment * 2, n - 1);
}

int main() {
  int n;
  while (cin >> n) {
    int len = 1;
    for (int i = 0; i < n; ++i) len *= 3;

    string a(len, '-');
    cantor(a, 0, n);

    cout << a << endl;
  }
}