#include <iostream>
#include <vector>
using namespace std;

int n, m;
bool* visited;

void backtrack(vector<int>& result) {
  if (result.size() == m) {
    for (auto i : result) cout << i << " ";
    cout << "\n";
    return;
  }

  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      visited[i] = true;
      result.push_back(i);

      backtrack(result);

      result.pop_back();
      visited[i] = false;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  visited = new bool[n + 1];
  for (int i = 1; i <= n; ++i) visited[i] = false;

  vector<int> result;
  backtrack(result);

  delete[] visited;
}