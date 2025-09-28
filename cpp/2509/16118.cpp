#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
using ll = long long;

const ll INF = 2e10;

struct Node {
  int index;
  ll dist;
  bool can_run;

  bool operator <(const Node& other) const {
    return dist > other.dist;
  }
};

int n, m;
vector<Node> graph[4001];
ll fox_dp[4001];
ll wolf_dp[4001][2];

void dijkstra(int start) {
  priority_queue<Node> fox_pq;
  fox_pq.push({ start, 0, false });
  fox_dp[start] = 0;

  while (!fox_pq.empty()) {
    Node cur = fox_pq.top();
    fox_pq.pop();

    if (cur.dist > fox_dp[cur.index]) continue;

    for (Node next : graph[cur.index]) {
      if (fox_dp[next.index] > cur.dist + next.dist) {
        fox_dp[next.index] = cur.dist + next.dist;
        fox_pq.push({ next.index, fox_dp[next.index], false });
      }
    }
  }

  priority_queue<Node> wolf_pq;
  wolf_pq.push({ start, 0, true });
  wolf_dp[start][0] = 0;

  while (!wolf_pq.empty()) {
    Node cur = wolf_pq.top();
    wolf_pq.pop();

    if (cur.can_run && cur.dist > wolf_dp[cur.index][0]) continue;
    if (!cur.can_run && cur.dist > wolf_dp[cur.index][1]) continue;

    if (cur.can_run) {
      for (Node next : graph[cur.index]) {
        if (wolf_dp[next.index][1] > cur.dist + (next.dist / 2)) {
          wolf_dp[next.index][1] = cur.dist + (next.dist / 2);
          wolf_pq.push({ next.index, wolf_dp[next.index][1], false });
        }
      }
    } else {
      for (Node next : graph[cur.index]) {
        if (wolf_dp[next.index][0] > cur.dist + (next.dist * 2)) {
          wolf_dp[next.index][0] = cur.dist + (next.dist * 2);
          wolf_pq.push({ next.index, wolf_dp[next.index][0], true });
        }
      }
    }
  }
}

int main() {
  scanf("%d %d", &n, &m);

  for (int i = 1; i <= m; i++) {
    int a, b;
    ll d;
    scanf("%d %d %lld", &a, &b, &d);
    graph[a].push_back({ b, d * 2, false });
    graph[b].push_back({ a, d * 2, false });
  }

  for (int i = 1; i <= n; i++) {
    fox_dp[i] = INF;
    wolf_dp[i][0] = wolf_dp[i][1] = INF;
  }

  dijkstra(1);

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (fox_dp[i] < min(wolf_dp[i][0], wolf_dp[i][1])) ans++;
  }
  printf("%d\n", ans);
}