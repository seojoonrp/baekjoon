#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 1e6 + 5;

string n;
int k;
bool visited[11][MAX];


int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> k;
  int digit = n.size();

  queue<string> q;
  q.push(n);

  int cur_k = 0;
  while (!q.empty() && cur_k < k) {
    int qsize = q.size();

    for (int s = 0; s < qsize; s++) {
      string cur = q.front();
      q.pop();

      for (int i = 0; i < digit; i++) {
        for (int j = i + 1; j < digit; j++) {
          swap(cur[i], cur[j]);

          if (cur[0] != '0' && !visited[cur_k + 1][stoi(cur)]) {
            visited[cur_k + 1][stoi(cur)] = true;
            q.push(cur);
          }

          swap(cur[i], cur[j]);
        }
      }
    }

    cur_k++;
  }

  int ans = -1;
  while (!q.empty()) {
    ans = max(ans, stoi(q.front()));
    q.pop();
  }
  cout << ans << '\n';
}