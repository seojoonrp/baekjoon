#include <iostream>
#include <string>
#include <vector>
using namespace std;

int n, m;
string text, pattern;
int failure[1000001];
vector<int> ans;

void failure_function() {
  failure[0] = 0;

  int lo = 0;
  int hi = 1;

  while (hi < m) {
    if (pattern[lo] == pattern[hi]) {
      failure[hi] = lo + 1;
      lo++;
      hi++;
    } else if (lo > 0) {
      lo = failure[lo - 1];
    } else {
      failure[hi] = 0;
      hi++;
    }
  }
}

void kmp() {
  failure_function();

  int t = 0;
  int p = 0;

  while (t < n) {
    if (text[t] == pattern[p]) {
      if (p == m - 1) {
        ans.push_back(t - p);
        t++;
        p = failure[p];
      } else {
        t++;
        p++;
      }
    } else if (p > 0) {
      p = failure[p - 1];
    } else {
      t++;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  getline(cin, text);
  getline(cin, pattern);
  n = text.length();
  m = pattern.length();

  if (m > n) {
    printf("0\n");
    return 0;
  }

  kmp();

  cout << ans.size() << '\n';
  for (int x : ans) cout << x + 1 << ' ';
  cout << '\n';
}