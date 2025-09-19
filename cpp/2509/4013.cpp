#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
  int value;
  bool visited;
  vector<int> linked;
  vector<int> linked_t;
  int scc;
  bool rest;
};

struct SCC {
  int value;
  vector<int> linked;
  int indegree;
  bool rest;
};

int n, m;
Node nodes[500001];
int start, p;

stack<int> stk;
int scc_len = 1; // 1-based
int dp[500001];
SCC sccs[500001];
vector<int> sorted_scc_index;

void first_dfs(int node) {
  nodes[node].visited = true;

  for (int next : nodes[node].linked) {
    if (!nodes[next].visited) first_dfs(next);
  }

  stk.push(node);
}

void find_scc(int node, int scc_index) {
  nodes[node].visited = true;
  nodes[node].scc = scc_index;

  sccs[scc_index].value += nodes[node].value;
  if (nodes[node].rest) sccs[scc_index].rest = true;

  for (int next : nodes[node].linked_t) {
    Node& next_node = nodes[next];
    if (next_node.visited) {
      if (next_node.scc != scc_index) {
        sccs[next_node.scc].linked.push_back(scc_index);
        sccs[scc_index].indegree++;
      }
    } else {
      find_scc(next, scc_index);
    }
  }
}

void topology_sort() {
  bool flag = false;
  queue<int> q;

  for (int i = 1; i <= scc_len; ++i) {
    if (sccs[i].indegree == 0) {
      sorted_scc_index.push_back(i);
      q.push(i);
    }
  }

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    if (cur == nodes[start].scc) flag = true;

    for (int next : sccs[cur].linked) {
      sccs[next].indegree--;
      if (sccs[next].indegree == 0) {
        sorted_scc_index.push_back(next);
        q.push(next);
      }

      if (flag && dp[cur] != -1) dp[next] = max(dp[next], dp[cur] + sccs[next].value);
    }
  }
}

int main() {
  scanf("%d %d", &n, &m);

  for (int i = 0; i < m; ++i) {
    int from, to;
    scanf("%d %d", &from, &to);
    nodes[from].linked.push_back(to);
    nodes[to].linked_t.push_back(from);
  }

  for (int i = 1; i <= n; ++i) scanf("%d", &nodes[i].value);

  scanf("%d %d", &start, &p);

  for (int i = 0; i < p; ++i) {
    int node;
    scanf("%d", &node);
    nodes[node].rest = true;
  }

  for (int i = 1; i <= n; ++i) {
    if (!nodes[i].visited) first_dfs(i);
  }

  for (int i = 1; i <= n; ++i) nodes[i].visited = false;

  while (!stk.empty()) {
    int cur_root = stk.top();
    if (!nodes[cur_root].visited) {
      find_scc(cur_root, scc_len);
      scc_len++;
    }
    stk.pop();
  }
  scc_len--;

  for (int i = 1; i <= scc_len; ++i) {
    vector<int>& vec = sccs[i].linked;
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    dp[i] = -1;
  }

  dp[nodes[start].scc] = sccs[nodes[start].scc].value;
  topology_sort();

  int ans = 0;
  for (int i = 1; i <= scc_len; ++i) {
    if (sccs[i].rest) ans = max(ans, dp[i]);
  }

  printf("%d\n", ans);
}