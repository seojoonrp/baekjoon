#include <iostream>
#include <vector>
using namespace std;

const int MAX = 102;

int n, m;
int A[MAX], B[MAX];
vector<int> dp[MAX][MAX];

bool is_bigger(vector<int>& v1, vector<int>& v2) {
  int idx = 0;
  
  while (idx < (int)v1.size() && idx < (int)v2.size()) {
    if (v1[idx] > v2[idx]) return true;
    if (v1[idx] < v2[idx]) return false;
    idx++;
  }

  if (idx == (int)v1.size()) return false;
  else return true;
}

vector<int> calc(vector<int>& orig, int x) {
  vector<int> res;

  for (int num : orig) {
    if (x > num) {
      res.push_back(x);
      return res;
    } else {
      res.push_back(num);
    }
  }

  res.push_back(x);
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> A[i];
  cin >> m;
  for (int i = 1; i <= m; i++) cin >> B[i];

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (A[i] == B[j]) {
        dp[i][j] = calc(dp[i - 1][j - 1], A[i]);
      } else {
        if (is_bigger(dp[i - 1][j], dp[i][j - 1])) dp[i][j] = dp[i - 1][j];
        else dp[i][j] = dp[i][j - 1];
      }
    }
  }

  cout << dp[n][m].size() << '\n';
  for (int x : dp[n][m]) cout << x << ' ';
  cout << '\n';
}