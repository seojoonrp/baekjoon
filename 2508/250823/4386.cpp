#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <sstream>
using namespace std;

struct edge {
  int node1, node2;
  double cost;
};

int n;
vector<edge> edges;
pair<double, double> points[102];
int parent[102];
double ans;

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

  if (parent1 == parent2) return true;

  if (parent1 > parent2) parent[parent1] = parent2;
  else parent[parent2] = parent1;

  return false;
}

void kruskal() {
  sort(edges.begin(), edges.end(), compareByCost);
  for (int i = 0; i < n; ++i) parent[i] = i;
  int picked = 0;

  for (auto& e : edges) {
    bool isCycle = unionNodes(e.node1, e.node2);
    if (!isCycle) {
      ans += e.cost;
      if (++picked == n - 1) break;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 0; i < n; ++i) cin >> points[i].first >> points[i].second;

  for (int i = 0; i < n - 1; ++i) {
    for (int j = i + 1; j < n; ++j) {
      double dx = points[i].first - points[j].first;
      double dy = points[i].second - points[j].second;
      double cost = sqrt(dx * dx + dy * dy);
      edges.push_back({ i, j, cost });
    }
  }

  kruskal();

  cout << fixed;
  cout.precision(3);
  cout << ans << '\n';
}