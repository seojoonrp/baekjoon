#include <iostream>
#include <vector>
using namespace std;

struct Node {
  int index;
  int cost;
};

int n;
vector<Node> tree[10001];
bool visited[10001];
int max_dist, max_node;

void dfs(int node, int dist) {
  if (visited[node]) return;
  
  if (dist > max_dist) {
    max_dist = dist;
    max_node = node;
  }

  visited[node] = true;

  for (auto& next : tree[node]) {
    if (!visited[next.index]) {
      dfs(next.index, dist + next.cost);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n - 1; ++i) {
    int from, to, cost;
    cin >> from >> to >> cost;
    tree[from].push_back({ to, cost });
    tree[to].push_back({ from, cost });
  }

  dfs(1, 0);

  for (int i = 1; i <= n; ++i) visited[i] = false;
  max_dist = 0;

  dfs(max_node, 0);

  cout << max_dist << '\n';
}