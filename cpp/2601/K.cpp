#include <iostream>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAX = 1e5 + 5;

struct Point {
  int x, y, d;
};

int n, m;
int parent[MAX];
map<int, int> dist_parent;
Point points[MAX];

int find_parent(int x) {
  if (parent[x] == x) return x;
  return parent[x] = find_parent(parent[x]);
}

void union_nodes(int x, int y) {
  int px = find_parent(x);
  int py = find_parent(y);
  if (px != py) parent[px] = py;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> points[i].x >> points[i].y;
    points[i].d = abs(points[i].x) + abs(points[i].y);
    parent[i] = i;
  }

  for (int i = 0; i < n; i++) {
    int cur_d = points[i].d;
    if (dist_parent.count(cur_d)) union_nodes(i, dist_parent[cur_d]);
    dist_parent[cur_d] = find_parent(i);
  }

  cin >> m;
  while (m--) {
    int l; cin >> l;

    auto it = dist_parent.upper_bound(l);
    if (it == dist_parent.begin()) continue;

    it--;

    int cur_d = it->first;
    if (cur_d == 0) continue;

    int cur_p = find_parent(it->second);
    dist_parent.erase(it);

    int next_d = cur_d - 1;
    if (dist_parent.count(next_d)) {
      int next_p = find_parent(dist_parent[next_d]);
      union_nodes(cur_p, next_p);
      dist_parent[next_d] = find_parent(next_p);
    } else {
      dist_parent[next_d] = cur_p;
    }
  }

  
}