#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
vector<int> graph[1002];
int indegree[1002];

vector<int> topologySort() {
  vector<int> ans;
  queue<int> q;

  for (int i = 1; i <= n; ++i) {
    if (indegree[i] == 0) q.push(i);
  }

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    ans.push_back(cur);

    for (auto& next : graph[cur]) {
      indegree[next]--;
      if (indegree[next] == 0) q.push(next);
    }
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> m;
  while (m--) {
    int curlen;
    cin >> curlen;
    
    vector<int> curdata;
    while (curlen--) {
      int x;
      cin >> x;
      curdata.push_back(x);
    }

    for (int i = 0; i < curdata.size() - 1; ++i) {
      for (int j = i + 1; j < curdata.size(); ++j) {
        graph[curdata[i]].push_back(curdata[j]);
        indegree[curdata[j]]++;
      }
    }
  }

  vector<int> ans = topologySort();
  if (ans.size() < n) cout << 0 << '\n';
  else {
    for (auto& x : ans) cout << x << '\n';
  }
}