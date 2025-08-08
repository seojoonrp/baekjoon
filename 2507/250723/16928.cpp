#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int n = 100;
int a, b;
vector<pair<int, int>> ladder_snake;
int visited[n + 3];

bool compare(const pair<int, int>& a, const pair<int, int>& b) {
  return a.first < b.first;
}

void bfs(int start) {
  queue<int> q;

  q.push(start);
  visited[start] = 0;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    // cout << cur << endl;

    for (int dice = 1; dice <= 6; ++dice) {
      int next = cur + dice;

      if (next <= 100 && visited[next] == 0) {
        visited[next] = visited[cur] + 1;

        // 이진탐색으로 하면 더 빠를듯
        bool isConnected = false;
        for (int i = 0; i < ladder_snake.size(); ++i) {
          if (ladder_snake[i].first == next) {
            isConnected = true;
            int connectedNext = ladder_snake[i].second;

            if (visited[connectedNext] == 0) {
              visited[connectedNext] = visited[next];
              q.push(connectedNext);
            }
          }
        }

        if (!isConnected) q.push(next);
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> a >> b;

  for (int i = 0; i < a + b; ++i) {
    int x, y;
    cin >> x >> y;
    ladder_snake.push_back({x, y});
  }

  sort(ladder_snake.begin(), ladder_snake.end(), compare);

  bfs(1);

  cout << visited[n] << "\n";
}