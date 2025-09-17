#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> primes;

void find_next_prime() {
  int ret = primes[primes.size() - 1] + 1;
  
  while (true) {
    bool is_prime = true;

    for (auto& p : primes) {
      if (p * p > ret) break;
      if (ret % p == 0) {
        is_prime = false;
        break;
      }
    }

    if (is_prime) break;
    ret++;
  }

  primes.push_back(ret);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  primes.push_back(2);

  int lower = 0, upper = 0;
  int cur_sum = primes[lower];
  int ans = 0;

  while (true) {
    if (cur_sum == n) {
      ans++;

      cur_sum -= primes[lower];
      lower++;
      
      find_next_prime();
      upper++;
      if (primes[upper] > n) break;
      cur_sum += primes[upper];
    } else if (cur_sum < n) {
      find_next_prime();
      upper++;
      if (primes[upper] > n) break;
      cur_sum += primes[upper];
    } else {
      cur_sum -= primes[lower];
      lower++;
    }
  }

  cout << ans << '\n';
}