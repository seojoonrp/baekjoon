#include <iostream>
#include <queue>
using namespace std;

const int MAX_COORD = 100000;

int n, k;
int visited[100002];

bool isSafe(int x) {
  if (x < 0 || x > MAX_COORD) return false;
  return true;
}

int main() {
  cin >> n >> k;

  queue<int> q;
  q.push(n);
  visited[n] = 1;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    int next[3] = { cur - 1, cur + 1, cur * 2 };
    for (int i = 0; i < 3; ++i) {
      if (isSafe(next[i]) && !visited[next[i]]) {
        visited[next[i]] = visited[cur] + 1;
        q.push(next[i]);

        if (next[i] == k) break;
      }
    }
  }

  cout << visited[k] - 1 << '\n';
}