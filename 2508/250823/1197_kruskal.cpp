#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge {
  int node1;
  int node2;
  int cost;
};

int v, e;
vector<edge> edges;
int parent[10002];

bool compareByCost(const edge& e1, const edge& e2) {
  if (e1.cost != e2.cost) return e1.cost < e2.cost;
  if (e1.node1 != e2.node1) return e1.node1 < e2.node1;
  return e1.node2 < e2.node2;
}

int findParent(int node) {
  if (parent[node] == node) return node;

  parent[node] = findParent(parent[node]);
  return parent[node];
}

bool unionNodes(int node1, int node2) {
  int parent1 = findParent(node1);
  int parent2 = findParent(node2);

  if (parent1 == parent2) return true; // 이 edge로 인해 사이클이 생기는 경우 (연결X)

  // 번호가 더 작은 걸 부모로 설정
  if (parent1 > parent2) parent[parent1] = parent2;
  else parent[parent2] = parent1;

  return false;
}

vector<edge> kruskal() {
  vector<edge> ans;

  for (auto& e : edges) {
    bool isCycle = unionNodes(e.node1, e.node2);

    if (!isCycle) {
      ans.push_back(e);
    }
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> v >> e;
  while (e--) {
    int node1, node2, cost;
    cin >> node1 >> node2 >> cost;
    edges.push_back({ node1, node2, cost });
  }

  sort(edges.begin(), edges.end(), compareByCost);
  for (int i = 1; i <= v; ++i) parent[i] = i;

  vector<edge> ans = kruskal();
  int costSum = 0;
  for (auto& e : ans) costSum += e.cost;
  cout << costSum << '\n';
}