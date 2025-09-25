#include <cstdio>
#include <vector>
#include <stack>
using namespace std;

int n, m;
int interest[101][5];
int like[101][2];
int lake_graph[101][101];

vector<int> sat_graph[201], sat_graph_t[201];
stack<int> stk;
bool visited[201];
int scc[201];

int ans[101];

int NOT(const int& x) {
  return x > n ? x - n : x + n;
}

void make_clause(const int& i, const int& j) {
  sat_graph[NOT(i)].push_back(j);
  sat_graph[NOT(j)].push_back(i);
  sat_graph_t[j].push_back(NOT(i));
  sat_graph_t[i].push_back(NOT(j));
}
void clause_by_like(const int& i, const int& j) {
  if (like[i][0] == like[j][0]) make_clause(NOT(i), NOT(j));
  if (like[i][1] == like[j][0]) make_clause(i, NOT(j));
  if (like[i][0] == like[j][1]) make_clause(NOT(i), j);
  if (like[i][1] == like[j][1]) make_clause(i, j);
}
void check_log(const int& i, const int& j, const int& li, const int& lj) {
  int cur_interest = lake_graph[like[i][li]][like[j][lj]];
  int cur_i = li ? NOT(i) : i;
  int cur_j = lj ? NOT(j) : j;

  if (cur_interest) {
    if (interest[i][cur_interest] != interest[j][cur_interest]) {
      make_clause(NOT(cur_i), NOT(cur_j));
    }
  }
}
void clause_by_log(const int& i, const int& j) {
  check_log(i, j, 0, 0);
  check_log(i, j, 1, 0);
  check_log(i, j, 0, 1);
  check_log(i, j, 1, 1);
}

void fill_stack(const int& node) {
  visited[node] = true;

  for (int& next : sat_graph[node]) {
    if (!visited[next]) fill_stack(next);
  }

  stk.push(node);
}
void find_scc(const int& node, const int& scc_index) {
  scc[node] = scc_index;

  for (int& next : sat_graph_t[node]) {
    if (!scc[next]) find_scc(next, scc_index);
  }
}

void input() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i++) {
    for(int j = 1; j <= 4; j++) scanf("%d", &interest[i][j]);
  }
  for (int i = 1; i <= n; i++) scanf("%d %d", &like[i][0], &like[i][1]);
  for (int i = 1; i <= m; i++) {
    int n1, n2, interest;
    scanf("%d %d %d", &n1, &n2, &interest);
    lake_graph[n1][n2] = lake_graph[n2][n1] = interest;
  }
}

int main() {
  input();

  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      clause_by_like(i, j);
      clause_by_log(i, j);
    }
  }

  for (int i = 1; i <= 2 * n; i++) {
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
      printf("NO\n");
      return 0;
    }
  }
  printf("YES\n");

  for (int i = 1; i <= n; i++) {
    if (scc[i] > scc[NOT(i)]) ans[like[i][0]] = i;
    else ans[like[i][1]] = i;
  }
  for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
  printf("\n");

  return 0;
}