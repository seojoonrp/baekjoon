#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 일단 순서대로 다 그래프를 연결하고
// 바뀌는거의 그래프 순서를 뒤집는다.
// 그리고 위상정렬을 하는데
// 진입차수가 0인게 두 개 이상인 상황이 나오면 ?를,
// 사이클이 발생하면, 즉 방문한 노드 개수가 n보다 작으면 불가능을,
// 아니면 그냥 출력한다.

int n;
vector<int> graph[502];
int last_rank[502];
int indegree[502];
int temp_indegree[502];

string topologySort() {
  queue<int> q;
  vector<int> ans;
  bool unique = true;

  for (int i = 1; i <= n; ++i) {
    if (indegree[i] == 0) q.push(i);
  }
  if (q.size() > 1) unique = false;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    ans.push_back(cur);

    for (auto& next : graph[cur]) {
      indegree[next]--;
      if (indegree[next] == 0) {
        q.push(next);
      }
    }

    if (q.size() > 1) unique = false;
  }

  if (ans.size() < n) return "IMPOSSIBLE";
  else if (!unique) return "?";
  else {
    string res = "";
    for (auto& num : ans) res += to_string(num) + " ";
    return res;
  }
}

void initialize() {
  for (int i = 0; i < n; ++i) last_rank[i] = 0;
  for (int i = 1; i <= n; ++i) {
    graph[i].clear();
    indegree[i] = temp_indegree[i] = 0;
  }
  n = 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;

  while (T--) {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> last_rank[i];
    for (int i = 0; i < n; ++i) {
      indegree[last_rank[i]] = temp_indegree[last_rank[i]] = i;
      for (int j = i + 1; j < n; ++j) graph[last_rank[i]].push_back(last_rank[j]);
    }

    int m;
    cin >> m;
    if (m == 0) {
      for (int i = 0; i < n; ++i) cout << last_rank[i] << " ";
      cout << "\n";
      initialize();
      continue;
    }

    while (m--) {
      int x, y;
      cin >> x >> y;
      int higher = temp_indegree[x] > temp_indegree[y] ? x : y;
      int lower = temp_indegree[x] < temp_indegree[y] ? x : y;

      indegree[lower]++;
      indegree[higher]--;
      auto it = find(graph[lower].begin(), graph[lower].end(), higher);
      graph[lower].erase(it);
      graph[higher].push_back(lower);
    }

    cout << topologySort() << "\n";

    initialize();
  }
}