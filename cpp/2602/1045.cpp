#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

const int MAX = 50 + 5;

struct Edge {
  int a, b;
};

bool cmp_edge(const Edge& e1, const Edge& e2) {
  if (e1.a == e2.a) return e1.b < e2.b;
  return e1.a < e2.a;
}

int n, m;
vector<Edge> edges;
int degree[MAX];
int parent[MAX];

int find_root(int x) {
  if (parent[x] == x) return x;
  return parent[x] = find_root(parent[x]);
}

void union_roots(int r1, int r2) {
  if (r1 == r2) return;

  if (r1 < r2) parent[r1] = r2;
  else parent[r2] = r1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  int surplus = m - (n - 1);

  for (int i = 0; i < n; i++) {
    string row; cin >> row;
    for (int j = i + 1; j < n; j++) {
      if (row[j] == 'Y') edges.push_back({i, j});
    }
  }

  sort(edges.begin(), edges.end(), cmp_edge);

  for (int i = 0; i < n; i++) parent[i] = i;

  int surp_cnt = 0;
  for (Edge& e : edges) {
    int ar = find_root(e.a);
    int br = find_root(e.b);

    if (ar != br) {
      union_roots(ar, br);
      degree[e.a]++;
      degree[e.b]++;
    } else if (surp_cnt < surplus) {
      surp_cnt++;
      degree[e.a]++;
      degree[e.b]++;
    }
  }

  int root = find_root(0);
  bool connected = true;
  for (int i = 1; i < n; i++) {
    if (find_root(i) != root) {
      connected = false;
      break;
    }
  }

  if (!connected || surp_cnt != surplus) cout << -1 << '\n';
  else {
    for (int i = 0; i < n; i++) {
      cout << degree[i] << ' ';
    }
    cout << '\n';
  }
}