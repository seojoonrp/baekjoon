#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n;
vector<int> tree[1000001];
bool visited[1000001];

pair<int, int> solve(int node) {
  visited[node] = true;

  pair<int, int> ret = { 1, 0 };
  for (int& next : tree[node]) {
    if (!visited[next]) {
      pair<int, int> next_solve = solve(next);
      ret.first += min(next_solve.first, next_solve.second);
      ret.second += next_solve.first;
    }
  }

  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n - 1; ++i) {
    int node1, node2;
    cin >> node1 >> node2;
    tree[node1].push_back(node2);
    tree[node2].push_back(node1);
  }

  pair<int, int> ans = solve(1);
  cout << min(ans.first, ans.second) << '\n';
}