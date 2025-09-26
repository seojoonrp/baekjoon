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
  return x > n ? x - n : x + n;
}

void fill_stack(int node) {
  visited[node] = true;

  for (int next : graph[node]) {
    if (!visited[next]) fill_stack(next);
  }

  stk.push(node);
}

void find_scc(int node, int scc_index) {
  scc[node] = scc_index;

  for (int next : graph_t[node]) {
    if (!scc[next]) find_scc(next, scc_index);
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
    if (!visited[i]) fill_stack(i);
  }

  int scc_index = 1;
  while (!stk.empty()) {
    int cur_root = stk.top();
    stk.pop();

    if (!scc[cur_root]) {
      find_scc(cur_root, scc_index);
      scc_index++;
    }
  }

  for (int i = 1; i <= n; i++) {
    if (scc[i] == scc[NOT(i)]) {
      printf("0\n");
      return 0;
    }
  }
  printf("1\n");

  for (int i = 1; i <= n; i++) {
    // printf("%d %d ", scc[i], scc[NOT(i)]);
    if (scc[i] > scc[NOT(i)]) printf("1 ");
    else printf("0 ");
  }
  printf("\n");
}