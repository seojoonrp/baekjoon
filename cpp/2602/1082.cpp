#include <iostream>
using namespace std;

const int N_MAX = 10;
const int M_MAX = 51;

int n, m;
int price[N_MAX];
string dp[N_MAX][M_MAX];

bool is_bigger(const string& a, const string& b) {
  if (a.size() != b.size()) return a.size() > b.size();
  for (int i = 0; i < (int)a.size(); i++) {
    if (a[i] != b[i]) return a[i] > b[i];
  }
  return false;
}

string memo(int cur, int budget) {
  if (dp[cur][budget] != "!") return dp[cur][budget];

  if (cur == 0) {
    if (budget == m) return "0";

    string ret = "";
    for (int i = 0; i < (budget / price[cur]); i++) ret += "0";
    return dp[cur][budget] = ret;
  }

  int cur_price = 0;
  string prefix = "";
  string ret = "";
  while (cur_price <= budget) {
    string s = prefix + memo(cur - 1, budget - cur_price);
    if (is_bigger(s, ret)){
      ret = s;
    }

    prefix += cur + '0';
    cur_price += price[cur];
  }

  return dp[cur][budget] = ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++) cin >> price[i];
  cin >> m;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= m; j++) dp[i][j] = "!";
  }

  cout << memo(n - 1, m) << '\n';
}