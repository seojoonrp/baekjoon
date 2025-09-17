#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> childs[51];
int dp[51];

bool bigger(int a, int b) { return a > b; }

int solve(int x) {
  if (dp[x] != -1) return dp[x];

  if (childs[x].empty()) return dp[x] = 0;

  vector<int> values;
  for (int child : childs[x]) {
    values.push_back(solve(child));
  }

  sort(values.begin(), values.end(), bigger);

  int& ret = dp[x];
  for (int i = 0; i < values.size(); ++i) {
    ret = max(ret, values[i] + i + 1);
  }

  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; ++i) {
    int parent;
    cin >> parent;
    if (i > 0) childs[parent].push_back(i);

    dp[i] = -1;
  }

  cout << solve(0) << '\n';
}