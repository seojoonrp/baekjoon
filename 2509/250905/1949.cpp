#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
int value[10001];
vector<int> tree[10001];
bool visited[10001];

// first(우수 마을일때), second(일반 마을일때)
pair<int, int> solve(int node) {
  visited[node] = true;
  pair<int, int> ret = { value[node], 0 };
  
  for (int next : tree[node]) {
    if (!visited[next]) {
      pair<int, int> next_solve = solve(next);
      ret.first += next_solve.second;
      ret.second += max(next_solve.first, next_solve.second);
      // 만약 다 second를 골라버리면 문제가 되지 않냐?
      // 그러면 자연스럽게 이 노드를 우수 마을로 선정한 게 답이 될 것. 굳이 따지지 않아도 됨
    }
  }

  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> value[i];
  for (int i = 0; i < n - 1; ++i) {
    int n1, n2;
    cin >> n1 >> n2;
    tree[n1].push_back(n2);
    tree[n2].push_back(n1);
  }

  pair<int, int> ans = solve(1);
  cout << max(ans.first, ans.second) << '\n';
}