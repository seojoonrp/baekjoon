#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

const int INF = 1e8;

struct Edge {
  int node1, node2;
  int dist;
};

int n, m;
int graph[201][201];
vector<Edge> edges;

void floyd_warshall() {
  for (int k = 1; k <= n; k++) {
    for (int j = 1; j <= n; j++) {
      for (int i = 1; i <= n; i++) {
        graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
      }
    }
  }
}

double burn_time(int start) {
  double ans = 0;

  for (const Edge& edge : edges) {
    double cur_ans;

    int faster = min(graph[start][edge.node1], graph[start][edge.node2]);
    int slower = max(graph[start][edge.node1], graph[start][edge.node2]);

    if (faster + edge.dist < slower) cur_ans = (double)(faster + edge.dist);
    else cur_ans = (double)slower + (faster + edge.dist - slower) / 2.0;

    ans = max(ans, cur_ans);
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i != j) graph[i][j] = INF;
    }
  }

  for (int i = 1; i <= m; i++) {
    int a, b, dist;
    cin >> a >> b >> dist;
    graph[a][b] = min(graph[a][b], dist);
    graph[b][a] = min(graph[b][a], dist);
    edges.push_back({ a, b, dist });
  }

  floyd_warshall();

  double ans = INF;
  for (int i = 1; i <= n; i++) {
    ans = min(ans, burn_time(i));
  }

  cout << fixed;
  cout.precision(1);
  cout << ans << '\n';
}