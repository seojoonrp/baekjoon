#include <iostream>
using namespace std;

int n, ans;
int graph[100002];
bool visited[100002];
bool finished[100002];

void dfs(int node) {
  visited[node] = true;
  int next = graph[node];

  if (!visited[next]) {
    dfs(next);
  } else {
    if (!finished[next]) {
      for (int i = next; i != node; i = graph[i]) ans++;
      ans++;
    }
  }

  finished[node] = true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      cin >> graph[i];
      visited[i] = 0;
      finished[i] = 0;
    }

    ans = 0;
    for (int i = 1; i <= n; ++i) {
      if (!visited[i]) dfs(i);
    }

    cout << n - ans << '\n';
  }
}