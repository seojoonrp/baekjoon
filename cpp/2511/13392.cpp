#include <iostream>
#include <string>
using namespace std;

const int MAX = 10001;
const int INF = 1e9;

int n;
int arr_i[MAX], arr_f[MAX];
int dp[MAX][10];

int turn_l(int init, int amount) {
  return (init + amount) % 10;
}

int dist_r(int from, int to) {
  if (to <= from) return from - to;
  else return from + 10 - to;
}

// dp[i][j]: i번째 나사까지 고려했을 때, (총 왼쪽 회전 수 % 10) = j인 최소 횟수
// 왼쪽: +1, 오른쪽: -1
int solve() {
  for (int j = 0; j < 10; j++) {
    dp[0][j] = j + dist_r(turn_l(arr_i[0], j), arr_f[0]);
  }
  
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < 10; j++) dp[i][j] = INF;

    for (int j = 0; j < 10; j++) {
      int init = turn_l(arr_i[i], j);

      for (int l = 0; l < 10; l++) {
        int total_l = (j + l) % 10;
        int req_r = dist_r(turn_l(init, l), arr_f[i]);

        dp[i][total_l] = min(dp[i][total_l], dp[i - 1][j] + l + req_r);
      }
    }
  }

  int ans = INF;
  for (int j = 0; j < 10; j++) {
    ans = min(ans, dp[n - 1][j]);
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;

  string sarr_i, sarr_f;
  cin >> sarr_i >> sarr_f;
  for (int i = 0; i < n; i++) {
    arr_i[i] = sarr_i[i] - '0';
    arr_f[i] = sarr_f[i] - '0';
  }

  cout << solve() << '\n';
}