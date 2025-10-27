#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 100001;

struct Node {
  int index;
  int dist;
};

struct cmp_node {
  bool operator()(const Node& n1, const Node& n2) {
    if (n1.dist == n2.dist) return n1.index > n2.index;
    else return n1.dist > n2.dist;
  }
};

int n, m;
vector<Node> graph[MAX];
int in_mst[MAX];
int max_path = -1;

int prim(int start) {
  int total_cost = 0;
  priority_queue<Node, vector<Node>, cmp_node> pq;

  in_mst[start] = true;
  for (Node& next : graph[start]) pq.push(next);

  while (!pq.empty()) {
    Node cur = pq.top();
    pq.pop();

    if (in_mst[cur.index]) continue;

    in_mst[cur.index] = true;
    total_cost += cur.dist;
    max_path = max(max_path, cur.dist);

    for (Node& next : graph[cur.index]) {
      if (!in_mst[next.index]) pq.push(next);
    }
  }

  return total_cost;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;

  for (int i = 1; i <= m; i++) {
    int a, b, dist;
    cin >> a >> b >> dist;
    graph[a].push_back({ b, dist });
    graph[b].push_back({ a, dist });
  }

  cout << prim(1) - max_path << '\n';
}