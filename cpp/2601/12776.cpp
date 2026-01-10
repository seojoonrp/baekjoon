#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

const int MAX = 1e6 + 5;

int n;
vector<pll> incr, decr;

bool incr_cmp(const pll& a, const pll& b) {
  if (a.first == b.first) return a.second < b.second;
  return a.first < b.first;
}
bool decr_cmp(const pll& a, const pll& b) {
  if (a.second == b.second) return a.first < b.second;
  return a.second > b.second;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++) {
    ll o, l;
    cin >> o >> l;

    if (o <= l) incr.push_back({ o, l });
    else decr.push_back({ o, l });
  }

  sort(incr.begin(), incr.end(), incr_cmp);
  sort(decr.begin(), decr.end(), decr_cmp);

  ll left = 0;
  ll extra = 0;

  for (auto& p : incr) {
    if (p.first > left) {
      extra += p.first - left;
      left = p.second;
    } else {
      left -= p.first;
      left += p.second;
    }
  }

  for (auto& p : decr) {
    if (p.first > left) {
      extra += p.first - left;
      left = p.second;
    } else {
      left -= p.first;
      left += p.second;
    }
  }

  cout << extra << '\n';
}