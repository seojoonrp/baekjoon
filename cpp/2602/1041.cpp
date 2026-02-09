#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
using ll = long long;

string edges[12] = {
  "AB",
  "AC",
  "AD",
  "AE",
  "BC",
  "BD",
  "BF",
  "CE",
  "CF",
  "DE",
  "DF",
  "EF",
};

string points[8] = {
  "ABC",
  "ABD",
  "ACE",
  "ADE",
  "BCF",
  "BDF",
  "CEF",
  "DEF",
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n; cin >> n;

  ll INF = 1e9;
  ll min1 = INF, min2 = INF, min3 = INF;

  ll dice[6];
  for (int i = 0; i < 6; i++) {
    cin >> dice[i];
    min1 = min(min1, dice[i]);
  }

  if (n == 1) {
    ll M = 0, ans = 0;
    for (int i = 0; i < 6; i++) {
      ans += dice[i];
      M = max(M, dice[i]);
    }
    ans -= M;
    cout << ans << '\n';
    return 0;
  }

  for (int i = 0; i < 12; i++) {
    ll cur = 0;
    for (char c : edges[i]) cur += dice[c - 'A'];
    min2 = min(min2, cur);
  }

  for (int i = 0; i < 8; i++) {
    ll cur = 0;
    for (char c : points[i]) cur += dice[c - 'A'];
    min3 = min(min3, cur);
  }

  ll ans = 0;
  ans += ((n - 2) * (n - 2) * 5 + (n - 2) * 4) * min1;
  ans += (((n - 2) + (n - 1)) * 4) * min2;
  ans += 4 * min3;
  cout << ans << '\n';
}