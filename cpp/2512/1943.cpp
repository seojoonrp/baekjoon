#include <iostream>
using namespace std;

const int N_MAX = 101;
const int V_MAX = 50001;

struct Coin {
  int value;
  int count;
};

int n;
Coin coins[N_MAX];
int dp_prev[V_MAX], dp_cur[V_MAX];

bool solve() {
  cin >> n;
  
  int total_value = 0;
  for (int i = 1; i <= n; i++) {
    cin >> coins[i].value >> coins[i].count;
    total_value += coins[i].value * coins[i].count;
  }
  if (total_value % 2 == 1) return false;

  int target_value = total_value / 2;

  for (int j = 0; j <= target_value; j++) dp_prev[j] = -1;
  dp_prev[0] = 0;

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= target_value; j++) {
      Coin& coin = coins[i];

      if (dp_prev[j] != -1) {
        dp_cur[j] = coin.count;
      } else if (j >= coin.value && dp_cur[j - coin.value] > 0) {
        dp_cur[j] = dp_cur[j - coin.value] - 1;
      } else {
        dp_cur[j] = -1;
      }
    }

    for (int j = 0; j <= target_value; j++) {
      dp_prev[j] = dp_cur[j];
    }
  }

  return dp_prev[target_value] != -1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  for (int tc = 0; tc < 3; tc++) {
    cout << (solve() ? 1 : 0) << '\n';
  }
}