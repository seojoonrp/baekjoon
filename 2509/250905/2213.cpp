#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
int value[10001];
vector<int> tree[10001];
bool visited[10001];
pair<int, int> dp[10001];
vector<int> ans_selected;

pair<int, int> solve(int cur) {
  visited[cur] = true;

  pair<int, int>& ret = dp[cur];
  ret = { value[cur], 0 };

  for (int next : tree[cur]) {
    if (visited[next]) continue;

    pair<int, int> next_solve = solve(next);
    ret.first += next_solve.second;
    ret.second += max(next_solve.first, next_solve.second);
  }

  return ret;
}

void trace(int cur, bool selected) {
  visited[cur] = true;

  if (selected) {
    ans_selected.push_back(cur);
    for (int next : tree[cur]) {
      if (visited[next]) continue;

      trace(next, false);
    }
  } else {
    for (int next : tree[cur]) {
      if (visited[next]) continue;

      trace(next, dp[next].first > dp[next].second);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> value[i];
  for (int i = 1; i <= n - 1; ++i) {
    int n1, n2;
    cin >> n1 >> n2;
    tree[n1].push_back(n2);
    tree[n2].push_back(n1);
  }

  pair<int, int> ans = solve(1);
  fill(visited + 1, visited + n + 1, false);
  
  if (ans.first > ans.second) {
    cout << ans.first << '\n';
    trace(1, true);
  } else {
    cout << ans.second << '\n';
    trace(1, false);
  }
  sort(ans_selected.begin(), ans_selected.end());
  for(int x : ans_selected) cout << x << ' ';
  cout << '\n';
}