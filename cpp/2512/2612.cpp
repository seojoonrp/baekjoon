#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 1001;

struct Memo {
  int value;
  int from; // 0, 1, 2, 3 -> Start, A, B, Diag
};

int n, m;
string A, B;
Memo dp[MAX][MAX];
// A에서 i, B에서 j로 끝나는 부분 서열 쌍

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> A;
  cin >> m >> B;

  int lcs_len = -1;
  int sx, sy;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      int score[4] = { 0, -1, -1, -1 };
      
      score[1] = dp[i - 1][j].value - 2;
      score[2] = dp[i][j - 1].value - 2;

      if (A[i - 1] == B[j - 1]) score[3] = dp[i - 1][j - 1].value + 3;
      else score[3] = dp[i - 1][j - 1].value - 2;

      int& max_val = dp[i][j].value;
      int max_idx = 0;
      for (int c = 1; c < 4; c++) {
        if (score[c] > max_val) {
          max_val = score[c];
          max_idx = c;
        }
      }
      dp[i][j].from = max_idx;

      if (lcs_len < max_val) {
        lcs_len = max_val;
        sx = i;
        sy = j;
      }
    }
  }

  cout << lcs_len << '\n';
  int x = sx, y = sy;
  
  while (true) {
    int from = dp[x][y].from;

    if (from == 0) break;
    if (from == 1) x--;
    if (from == 2) y--;
    if (from == 3) {
      x--;
      y--;
    }
  }

  for (int i = x + 1; i <= sx; i++) cout << A[i - 1];
  cout << '\n';
  for (int i = y + 1; i <= sy; i++) cout << B[i - 1];
  cout << '\n';
}