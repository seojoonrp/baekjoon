#include <iostream>
#include <string>
using namespace std;

struct num {
  int mod;
  int digit;
};

int n, k;
num arr[16];
int digit_mod[51];
long long dp[1 << 15][101]; // dp[mask][mod]

int get_mod(const string& s) {
  int ans = 0;

  for (int i = 0; i < s.length(); ++i) {
    ans *= 10;
    ans += s[i] - '0';
    ans %= k;
  }

  return ans;
}

void get_digit_mod() {
  digit_mod[0] = 1;
  for (int i = 1; i <= 50; ++i) {
    digit_mod[i] = (digit_mod[i - 1] * 10) % k;
  }
}

void solve() {
  dp[0][0] = 1;

  for (int mask = 0; mask < (1 << n); ++mask) {
    for (int cur_mod = 0; cur_mod < k; ++cur_mod) {
      for (int next = 0; next < n; ++next) {
        if (mask & (1 << next)) continue;

        num cur_num = arr[next];
        int next_mod = (cur_mod * digit_mod[cur_num.digit] + cur_num.mod) % k;
        dp[mask | (1 << next)][next_mod] += dp[mask][cur_mod];
      }
    }
  }
}

long long get_gcd(long long a, long long b) {
  long long big = b;
  long long small = a;
  
  while (big % small != 0) {
    long long r = big % small;
    big = small;
    small = r;
  }

  return small;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  string temp_numbers[16];
  for (int i = 0; i < n; ++i) cin >> temp_numbers[i];
  cin >> k;

  for (int i = 0; i < n; ++i) {
    num& num = arr[i];
    num.mod = get_mod(temp_numbers[i]);
    num.digit = temp_numbers[i].length();
  }

  get_digit_mod();

  solve();

  long long numer = dp[(1 << n) - 1][0];
  long long denom = 1;
  for (int i = 2; i <= n; ++i) denom *= i;

  if (numer == 0) {
    cout << "0/1\n";
    return 0;
  }
  if (numer == denom) {
    cout << "1/1\n";
    return 0;
  }

  long long gcd = get_gcd(numer, denom);
  cout << (numer / gcd) << '/' << (denom / gcd) << '\n';
}