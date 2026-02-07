#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int MAX = 55;
const string NUM = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int n, k;
string arr[MAX], gain[36];

int c2n(char c) {
  if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
  return c - '0';
}

string plus_36(string a, string b) {
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  while (a.size() > b.size()) b += '0';
  while (b.size() > a.size()) a += '0';
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());

  string res = "";
  int carry = 0;
  for (int i = a.size() - 1; i >= 0; i--) {
    int x = c2n(a[i]) + c2n(b[i]) + carry;
    if (x >= 36) {
      carry = 1;
      res += NUM[x - 36];
      if (i == 0) res += '1';
    } else {
      carry = 0;
      res += NUM[x];
    }
  }
  reverse(res.begin(), res.end());

  string final = "";
  bool first = false;
  for (char c : res) {
    if (!first && c == '0') continue;
    if (!first) first = true;
    final += c;
  }

  if (final == "") return "0";
  return final;
}

bool cmp_36(string& a, string& b) {
  if (a.size() != b.size()) return a.size() > b.size();

  for (int i = 0; i < (int)a.size(); i++) {
    if (a[i] == b[i]) continue;
    
    return a[i] > b[i];
  }

  return false;
}

string change_z_gain(string& s, char c) {
  string res = "";
  for (char cs : s) {
    if (cs == c) {
      res += NUM[c2n('Z') - c2n(c)];
    } else res += '0';
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++) cin >> arr[i];
  cin >> k;

  for (int i = 0; i < 36; i++) {
    char c = NUM[i];
    string res = "0";
    
    for (int i = 0; i < n; i++) {
      string g = change_z_gain(arr[i], c);
      res = plus_36(res, g);
    }

    gain[i] = res;
  }

  sort(gain, gain + 36, cmp_36);

  string ans = "0";
  for (int i = 0; i < n; i++) {
    ans = plus_36(ans, arr[i]);
  }
  for (int i = 0; i < k; i++) {
    ans = plus_36(ans, gain[i]);
  }

  cout << ans << '\n';
}