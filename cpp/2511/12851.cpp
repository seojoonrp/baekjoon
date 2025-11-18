#include <iostream>
#include <queue>
using namespace std;

const int MAX = 100001;

struct Node {
  int min_time;
  int ways;
};

Node nodes[MAX];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int sub, bro;
  cin >> sub >> bro;

  for (int i = 0; i < MAX; i++) {
    nodes[i].min_time = -1;
  }

  queue<int> q;
  q.push(sub);
  nodes[sub].min_time = 0;
  nodes[sub].ways = 1;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    if (cur == bro) {
      cout << nodes[cur].min_time << '\n';
      cout << nodes[cur].ways << '\n';
      return 0;
    }

    int poss[3] = { cur - 1, cur + 1, cur * 2 };

    for (int i = 0; i < 3; i++) {
      int next = poss[i];
      if (next < 0 || next >= MAX) continue;

      if (nodes[next].min_time == -1) {
        nodes[next].min_time = nodes[cur].min_time + 1;
        nodes[next].ways = nodes[cur].ways;

        q.push(next);
      } else {
        if (nodes[next].min_time == nodes[cur].min_time + 1) {
          nodes[next].ways += nodes[cur].ways;
        }
      }
    }
  }
}