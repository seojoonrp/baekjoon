#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, k;
vector<int> bn;

void get_bn() {
  int temp = n;
  while (temp > 0) {
    bn.push_back(temp % 2);
    temp /= 2;
  }
  reverse(bn.begin(), bn.end());
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> k;

  if (n <= k) {
    cout << 0 << '\n';
    return 0;
  }

  get_bn();

  int ones = 0;
  for (int x : bn) {
    if (x == 1) ones++;
  }
  if (ones <= k) {
    cout << 0 << '\n';
    return 0;
  }

  int cur_ones = 0;
  int ans = 0;
  for (int i = 0; i < (int)bn.size(); i++) {
    if (bn[i] == 1) {
      int shift = bn.size() - i - 1;

      if (cur_ones == k - 1) {
        ans += 1 << (shift + 1);
        break;
      }

      ans += 1 << shift;
      cur_ones++;
    }
  }

  cout << ans - n << '\n';
}