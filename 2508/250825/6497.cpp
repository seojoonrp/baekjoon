#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge {
  int node1, node2;
  int cost;
};

bool compareByCost(const edge& e1, const edge& e2) {
  if (e1.cost != e2.cost) return e1.cost < e2.cost;
  else if (e1.node1 != e2.node1) return e1.node1 < e2.node1;
  return e1.node2 < e2.node2;
}

int n, m;
vector<edge> edges;
int parent[200002];

int findParent(int node) {
  if (parent[node] == node) return node;

  parent[node] = findParent(parent[node]);
  return parent[node];
}

bool unionNodes(int node1, int node2) {
  int parent1 = findParent(node1);
  int parent2 = findParent(node2);

  if (parent1 == parent2) return true;

  if (parent1 < parent2) parent[parent2] = parent1;
  else parent[parent1] = parent2;

  return false;
}

int kruskal() {
  for (int i = 0; i < n; ++i) parent[i] = i;
  sort(edges.begin(), edges.end(), compareByCost);

  int ans = 0;

  for (auto& e : edges) {
    bool isCycle = unionNodes(e.node1, e.node2);
    if (!isCycle) {
      ans += e.cost;
    }
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  while (true) {
    cin >> n >> m;
    if (n == 0 && m == 0) break;

    int totalCost = 0;
    while (m--) {
      int node1, node2, cost;
      cin >> node1 >> node2 >> cost;

      edges.push_back({ node1, node2, cost });
      totalCost += cost;
    }

    cout << totalCost - kruskal() << '\n';

    edges.clear();
  }
}