#include <iostream>
#include <string>
using namespace std;

int n;
string s;
int failure[1000001];

void failure_func() {
  failure[0] = 0;

  int lo = 0;
  int hi = 1;

  while (hi < n) {
    if (s[lo] == s[hi]) {
      failure[hi] = lo + 1;
      lo++;
      hi++;
    } else if (lo > 0) {
      lo = failure[lo - 1];
    } else {
      failure[hi] = lo;
      hi++;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> s;

  failure_func();
  
  cout << n - failure[n - 1] << '\n';
}