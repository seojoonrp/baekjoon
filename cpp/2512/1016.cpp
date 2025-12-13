#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

const int MAX = 1000001;

bool is_prime[MAX];
vector<int> primes;
bool nosquare[MAX];

void fill_primes(int bound) {
  fill(is_prime, is_prime + bound + 2, true);
  is_prime[0] = is_prime[1] = false;

  for (int i = 2; i <= bound; i++) {
    if (!is_prime[i]) continue;

    primes.push_back(i);
    for (ll j = (ll)i * i; j <= bound; j += i) {
      is_prime[j] = false;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll lo, hi;
  cin >> lo >> hi;

  int max_root = (int)sqrt(hi);
  fill_primes(max_root);

  fill(nosquare, nosquare + (hi - lo) + 1, true);
  for (int p : primes) {
    ll pp = (ll)p * p;
    ll start_idx = ((lo + pp - 1) / pp) * pp;
    
    for (ll i = start_idx; i <= hi; i += pp) {
      nosquare[i - lo] = false;
    }
  }

  int ans = 0;
  for (int i = 0; i < hi - lo + 1; i++) {
    if (nosquare[i]) ans++;
  }

  cout << ans << '\n';
}