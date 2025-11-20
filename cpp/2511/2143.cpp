#include <iostream>
#include <unordered_map>
using namespace std;
using ll = long long;

const int MAX = 1001;

int t, n, m;
ll a_sum[MAX], b_sum[MAX];
unordered_map<ll, int> a_count, b_count;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> t;

  cin >> n;
  for (int i = 1; i <= n; i++) {
    ll x;
    cin >> x;
    a_sum[i] = a_sum[i - 1] + x;
  }

  cin >> m;
  for (int i = 1; i <= m; i++) {
    ll x;
    cin >> x;
    b_sum[i] = b_sum[i - 1] + x;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      ll s = a_sum[j] - a_sum[i - 1];
      if (a_count.find(s) == a_count.end()) {
        a_count.insert({ s, 1 });
      } else {
        a_count[s]++;
      }
    }
  }

  for (int i = 1; i <= m; i++) {
    for (int j = i; j <= m; j++) {
      ll s = b_sum[j] - b_sum[i - 1];
      if (b_count.find(s) == b_count.end()) {
        b_count.insert({ s, 1 });
      } else {
        b_count[s]++;
      }
    }
  }

  ll ans = 0;
  for (const auto& a : a_count) {
    ll target = t - a.first;
    if (b_count.find(target) != b_count.end()) {
      ans += (ll)a.second * b_count[target];
    }
  }

  cout << ans << '\n';
}