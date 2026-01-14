#include <iostream>
#include <vector>
#include <deque>
using namespace std;
using ll = long long;
using i128 = __int128_t;

const int MAX = 1e5 + 5;

// y = cost * x + dp
struct Line {
  ll a, b;
};

int n;
ll height[MAX], cost[MAX];

ll f(Line& l, ll x) {
  return l.a * x + l.b;
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

  for (int i = 1; i <= n; i++) cin >> height[i];
  for (int i = 1; i <= n; i++) cin >> cost[i];

  deque<Line> dq;
  dq.push_back({ cost[1], 0 });

  for (int i = 2; i <= n; i++) {
    ll x = height[i];

    while (dq.size() >= 2 && f(dq[1], x) < f(dq[0], x)) {
      dq.pop_front();
    }

    Line nl = { cost[i], f(dq[0], x) };

    while (dq.size() >= 2 &&
           should_pop(dq[dq.size() - 2], dq[dq.size() - 1], nl)) {
      dq.pop_back();
    }

    dq.push_back(nl);
  }

  cout << dq[dq.size() - 1].b << '\n';
}