#include <iostream>
#include <vector>
using namespace std;

int n, r, q;
vector<int> tree[100001];
int dp[100001];
bool visited[100001];

int solve(int node) {
  // if (dp[node] != -1) return dp[node];

  visited[node] = true;
  int& ret = dp[node];
  ret = 1;

  for (int& next : tree[node]) {
    if (!visited[next]) ret += solve(next);
  }

  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> r >> q;
  for (int i = 0; i < n - 1; ++i) {
    int node1, node2;
    cin >> node1 >> node2;
    tree[node1].push_back(node2);
    tree[node2].push_back(node1);
  }

  solve(r);

  while (q--) {
    int x;
    cin >> x;
    cout << dp[x] << '\n';
  }
}