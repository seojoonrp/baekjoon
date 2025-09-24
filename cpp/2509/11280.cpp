#include <cstdio>
#include <vector>
#include <stack>
using namespace std;

int n, m;
vector<int> graph[20001], graph_t[20001];
int scc[20001];
bool visited[20001];
stack<int> stk;

int NOT(const int& x) {
  if (x == n) return 2 * n;
  return (x + n) % (2 * n);
}

void first_dfs(int node) {
  visited[node] = true;

  for (int next : graph[node]) {
    if (!visited[next]) first_dfs(next);
  }

  stk.push(node);
}

void find_scc(int node, const int& scc_index) {
  visited[node] = true;
  scc[node] = scc_index;

  for (int next : graph_t[node]) {
    if (!visited[next]) find_scc(next, scc_index);
  }
}

int main() {
  scanf("%d %d", &n, &m);

  while (m--) {
    int a, b;
    scanf("%d %d", &a, &b);
    if (a < 0) a = -a + n;
    if (b < 0) b = -b + n;

    graph[NOT(a)].push_back(b);
    graph[NOT(b)].push_back(a);

    graph_t[b].push_back(NOT(a));
    graph_t[a].push_back(NOT(b));
  }

  for (int i = 1; i <= n * 2; i++) {
    if (!visited[i]) first_dfs(i);
  }

  fill(visited + 1, visited + (n * 2) + 1, false);

  int scc_cnt = 0;
  while (!stk.empty()) {
    int cur_root = stk.top();
    stk.pop();

    if (!visited[cur_root]) {
      find_scc(cur_root, scc_cnt);
      scc_cnt++;
    }
  }

  for (int i = 1; i <= n; i++) {
    if (scc[i] == scc[NOT(i)]) {
      printf("0\n");
      return 0;
    }
  }
  printf("1\n");
}