#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX = 1001;

int n;
vector<int> graph[MAX];
bool temp_graph[MAX][MAX];
bool visited[MAX], color[MAX];

bool make_bipartite(int start) {
  queue<int> q;
  q.push(start);
  visited[start] = true;
  color[start] = true;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (int next : graph[cur]) {
      if (visited[next] && color[next] == color[cur]) return false;

      if (!visited[next]) {
        visited[next] = true;
        color[next] = !color[cur];
        q.push(next);
      }
    }
  }

  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;

  int n1, n2;
  while (cin >> n1 >> n2) {
    if (n1 == -1 && n2 == -1) break;
    temp_graph[n1][n2] = true;
    temp_graph[n2][n1] = true;
  }

  for (int i = 1; i <= n; i++) {
    for (int to = 1; to <= n; to++) {
      if (to != i && !temp_graph[i][to]) graph[i].push_back(to);
    }
  }

  if (make_bipartite(1)) {
    cout << "1\n";
    for (int i = 1; i <= n; i++) {
      if (color[i]) cout << i << ' ';
    }
    cout << "-1\n";
    for (int i = 1; i <= n; i++) {
      if (!color[i]) cout << i << ' ';
    }
    cout << "-1\n";
  } else {
    cout << "-1\n";
  }
}