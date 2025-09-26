#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int n, k; // 편의상 문제랑 반대로 설정함
vector<int> graph[20001], graph_t[20001];
stack<int> stk;
int scc[20001];
bool visited[20001];

int NOT(const int& x) {
  return x > n ? x - n : x + n;
}

void make_edge(const int& a, const int& b, const int& c) {
  graph[NOT(a)].push_back(b);
  graph[NOT(a)].push_back(c);
  graph[NOT(b)].push_back(c);
  graph[NOT(b)].push_back(a);
  graph[NOT(c)].push_back(a);
  graph[NOT(c)].push_back(b);

  graph_t[b].push_back(NOT(a));
  graph_t[c].push_back(NOT(a));
  graph_t[c].push_back(NOT(b));
  graph_t[a].push_back(NOT(b));
  graph_t[a].push_back(NOT(c));
  graph_t[b].push_back(NOT(c));
}

void fill_stack(const int& node) {
  visited[node] = true;

  for (int next : graph[node]) {
    if (!visited[next]) fill_stack(next);
  }

  stk.push(node);
}

void find_scc(const int& node, const int& scc_index) {
  scc[node] = scc_index;

  for (int next : graph_t[node]) {
    if (!scc[next]) find_scc(next, scc_index);
  }
}

int main() {
  scanf("%d %d", &n, &k);

  for (int i = 1; i <= k; i++) {
    int a, b, c;
    char a_color, b_color, c_color;
    scanf("%d %c %d %c %d %c", &a, &a_color, &b, &b_color, &c, &c_color);

    if (a_color == 'B') a = NOT(a);
    if (b_color == 'B') b = NOT(b);
    if (c_color == 'B') c = NOT(c);

    make_edge(a, b, c);
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
      printf("-1\n");
      return 0;
    }
  }

  for (int i = 1; i <= n; i++) {
    if (scc[i] > scc[NOT(i)]) printf("R");
    else printf("B");
  }
  printf("\n");
}