#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

vector<int> adjacent(int idx) {
  vector<int> ret;
  if (idx - 3 >= 0) ret.push_back(idx - 3);
  if (idx + 3 <= 8) ret.push_back(idx + 3);
  if (idx % 3 != 0) ret.push_back(idx - 1);
  if (idx % 3 != 2) ret.push_back(idx + 1);
  return ret;
}

int solve(string target) {
  unordered_map<string, int> visited;
  queue<pair<string, int>> q;

  string start = "123456780";
  visited.insert({ start, 0 });
  q.push({ start, 8 });
  
  while (!q.empty()) {
    string cur_string = q.front().first;
    int cur_idx = q.front().second;
    q.pop();

    if (cur_string == target) return visited[cur_string];

    for (int next_idx : adjacent(cur_idx)) {
      string next_string = cur_string;
      swap(next_string[cur_idx], next_string[next_idx]);

      if (visited.find(next_string) == visited.end()) {
        visited[next_string] = visited[cur_string] + 1;
        q.push({ next_string, next_idx });
      }
    }
  }

  return -1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  string target = "";
  for (int i = 0; i < 9; i++) {
    int x;
    cin >> x;
    target += to_string(x);
  }

  cout << solve(target) << '\n';
}