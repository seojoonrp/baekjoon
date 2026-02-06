#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

vector<ll> results;
void backtrack(ll cur, ll last) {
  results.push_back(cur);
  
  for (ll i = 0; i < last; i++) {
    backtrack(10 * cur + i, i);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;

  for (ll i = 0; i < 10; i++) backtrack(i, i);

  sort(results.begin(), results.end());

  if (n < (int)results.size()) cout << results[n] << '\n';
  else cout << -1 << '\n';
}