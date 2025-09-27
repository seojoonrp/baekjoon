#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;

struct Node {
  int index;
  int dist;

  bool operator<(const Node& other) const {
    return dist > other.dist;
  }
};

int n, m;
int START, END;
int graph[501][501];
int dp[501];
vector<int> ans;

int dijkstra(int start, int end) {
  for (int i = 0; i < n; i++) dp[i] = INF;
  dp[start] = 0;
  
  priority_queue<Node> pq;
  pq.push({ start, 0 });

  while (!pq.empty()) {
    Node cur = pq.top();
    pq.pop();

    for (int i = 0; i < n; i++) {
      if (graph[cur.index][i]) {
        if (dp[i] > dp[cur.index] + graph[cur.index][i]) {
          dp[i] = dp[cur.index] + graph[cur.index][i];
          pq.push({ i, dp[i] });
        }
      }
    }
  }

  return (dp[end] == INF ? -1 : dp[end]);
}

void trace(int end) {
  queue<int> q;
  q.push(end);

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (int i = 0; i < n; i++) {
      if (graph[i][cur] && dp[i] != INF && dp[i] + graph[i][cur] == dp[cur]) {
        graph[i][cur] = 0;
        q.push(i);
      }
    }
  }
}

int main() {
  while (true) {
    scanf("%d %d", &n, &m);
    if (n == 0 && m == 0) break;

    scanf("%d %d", &START, &END);
    for (int i = 0; i < m; i++) {
      int from, to, dist;
      scanf("%d %d %d", &from, &to, &dist);
      graph[from][to] = dist;
    }

    if (dijkstra(START, END) == -1) ans.push_back(-1);
    else {
      trace(END);
      ans.push_back(dijkstra(START, END));
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) graph[i][j] = 0;
    }
  }

  for (int& x : ans) printf("%d\n", x);

  return 0;
}