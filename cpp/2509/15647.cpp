#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

struct Node {
  int index;
  int dist;
};

struct SubtreeInfo {
  ll dist_sum;
  int nodes;
};

int n;
vector<Node> tree[300001];
SubtreeInfo dp[300001];
ll ans[300001];

SubtreeInfo fill_dp(int cur) {
  SubtreeInfo& ret = dp[cur];
  ret.nodes = 1;

  for (Node& next : tree[cur]) {
    if (dp[next.index].nodes == 0) {
      SubtreeInfo next_res = fill_dp(next.index);
      ret.dist_sum += next_res.dist_sum + (next.dist * next_res.nodes);
      ret.nodes += next_res.nodes;
    }
  }

  return ret;
}

void change_root(int cur) {
  SubtreeInfo cur_backup = dp[cur];
  ans[cur] = dp[cur].dist_sum;

  for (Node& next : tree[cur]) {
    if (ans[next.index] == 0) {
      SubtreeInfo& next_dp = dp[next.index];
      SubtreeInfo next_backup = dp[next.index];
      
      ll other_dist_sum = dp[cur].dist_sum - next_dp.dist_sum - (next.dist * next_dp.nodes);
      int other_nodes = dp[cur].nodes - next_dp.nodes;

      dp[cur].nodes -= next_dp.nodes;
      dp[cur].dist_sum -= next_dp.dist_sum + (next.dist * next_dp.nodes);
      next_dp.nodes = n;
      next_dp.dist_sum += other_dist_sum + (next.dist * other_nodes);

      change_root(next.index);

      dp[cur] = cur_backup;
      next_dp = next_backup;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n - 1; ++i) {
    int n1, n2, dist;
    cin >> n1 >> n2 >> dist;
    tree[n1].push_back({ n2, dist });
    tree[n2].push_back({ n1, dist });
  }

  fill_dp(1);
  change_root(1);

  for (int i = 1; i <= n; ++i) cout << ans[i] << '\n';
}