#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX = 2e4 + 5;

struct Cow {
  int s, e;

  bool operator<(const Cow& other) const {
    return e > other.e;
  }
};

int c, n;
int chickens[MAX];
Cow cows[MAX];
priority_queue<Cow> pq;

bool cow_cmp(const Cow& c1, const Cow& c2) {
  return c1.s < c2.s;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> c >> n;

  for (int i = 0; i < c; i++) cin >> chickens[i];
  for (int i = 0; i < n; i++) {
    cin >> cows[i].s >> cows[i].e;
  }

  sort(chickens, chickens + c);
  sort(cows, cows + n, cow_cmp);

  int ans = 0;
  int cow_idx = 0;

  for (int i = 0; i < c; i++) {
    int ci = chickens[i];

    while (cow_idx < n && cows[cow_idx].s <= ci) {
      pq.push(cows[cow_idx]);
      cow_idx++;
    }

    while (!pq.empty()) {
      if (pq.top().e < ci) pq.pop();
      else break;
    }

    if (!pq.empty() && pq.top().e >= ci) {
      ans++;
      pq.pop();
    }
  }

  cout << ans << '\n';
}