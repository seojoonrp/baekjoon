#include <iostream>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

const int MAX = 55;

struct Row {
  int count;
  int zeros;
};

int n, m, k;
map<string, Row> rows;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    string row; cin >> row;
    int zeros = 0;

    if (rows.find(row) == rows.end()) {
      for (char c : row) {
        if (c == '0') zeros++;
      }

      rows.insert({row, {1, zeros}});
    } else {
      rows[row].count++;
    }
  }
  cin >> k;

  int ans = 0;
  for (auto it : rows) {
    Row row = it.second;
    if (row.zeros <= k && (row.zeros - k) % 2 == 0) {
      ans = max(ans, row.count);
    }
  }
  cout << ans << '\n';
}