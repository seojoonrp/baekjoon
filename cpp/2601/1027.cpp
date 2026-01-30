#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;

const int MAX = 50 + 5;

int n;
ll height[MAX];
bool see[MAX][MAX];

bool lower(int i, int m, int j) {
  ll LHS = (height[j] - height[i]) * (ll)(m - i);
  ll RHS = (height[m] - height[i]) * (ll)(j - i);
  return LHS <= RHS;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> height[i];

  for (int i = 1; i <= n; i++) {
    int m = i + 1;

    for (int j = i + 1; j <= n; j++) {
      if (j == i + 1) {
        see[i][j] = true;
        continue;
      }

      if (!lower(i, m, j)) {
        see[i][j] = true;
        m = j;
      }
    }
  }

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int cur = 0;
    for (int j = 1; j <= n; j++) {
      if (see[i][j] || see[j][i]) cur++;
    }
    ans = max(ans, cur);
  }
  cout << ans << '\n';
}