#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

struct Node {
  int index;
  int count;
};

int n, m;
vector<Node> graph[101];
int indegree[101];
int needed_parts[101][101];

void topology_sort() {
  queue<int> q;

  for (int i = 1; i <= n; i++) {
    if (indegree[i] == 0) {
      q.push(i);
      needed_parts[i][i] = 1;
    }
  }

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (Node next : graph[cur]) {
      indegree[next.index]--;
      if (indegree[next.index] == 0) {
        q.push(next.index);
      }

      for (int i = 1; i <= n; i++) {
        if (needed_parts[cur][i]) needed_parts[next.index][i] += needed_parts[cur][i] * next.count;
      }
    }
  }
}

int main() {
  scanf("%d %d", &n, &m);

  for (int i = 0; i < m; i++) {
    int to, from, count;
    scanf("%d %d %d", &to, &from, &count);
    graph[from].push_back({ to, count });
    indegree[to]++;
  }

  topology_sort();

  for (int i = 1; i <= n; i++) {
    if (needed_parts[n][i]) printf("%d %d\n", i, needed_parts[n][i]);
  }
}