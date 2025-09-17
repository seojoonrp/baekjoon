#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> tree[100003];
bool visited[100003];
int parent[100003];

void dfs(int cur, int par) {
  if (visited[cur]) return;

  visited[cur] = true;
  parent[cur] = par;

  for (auto& next : tree[cur]) {
    if (!visited[next]) {
      dfs(next, cur);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 0; i < n - 1; ++i) {
    int x, y;
    cin >> x >> y;
    tree[x].push_back(y);
    tree[y].push_back(x);
  }

  dfs(1, 0);

  for (int i = 2; i <= n; ++i) cout << parent[i] << "\n";
}