#include <iostream>
#include <vector>
#include <deque>
using namespace std;
using ll = long long;
using i128 = __int128_t;

const int MAX = 1e6 + 5;

struct Line {
  ll a, b;
  ll dp;
};

int n;
ll a, b, c;
ll s[MAX];

ll f(Line& l, ll x) {
  return l.a * x + l.b;
}

ll quad(ll x) {
  return a * x * x + b * x + c;
}

bool should_pop(Line& l1, Line& l2, Line& l3) {
  i128 o = (i128)(l2.b - l1.b) * (i128)(l2.a - l3.a);
  i128 n = (i128)(l3.b - l2.b) * (i128)(l1.a - l2.a);
  return o >= n;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  cin >> a >> b >> c;
  for (int i = 1; i <= n; i++) {
    ll x; cin >> x;
    s[i] = s[i - 1] + x;
  }

  deque<Line> dq;
  dq.push_back({ 0, 0, 0 });

  for (int i = 1; i <= n; i++) {
    ll x = s[i];

    while (dq.size() >= 2 && f(dq[1], x) > f(dq[0], x)) {
      dq.pop_front();
    }

    Line nl;
    nl.dp = f(dq[0], x) + quad(x);
    nl.a = -2 * a * x;
    nl.b = nl.dp + a * x * x - b * x;

    while (dq.size() >= 2 &&
           should_pop(dq[dq.size() - 2], dq.back(), nl)) {
      dq.pop_back();
    }

    dq.push_back(nl);
  }

  cout << dq.back().dp << '\n';
}