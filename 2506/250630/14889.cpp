#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

int n;
int** s;
int ans = INT_MAX;

vector<int> start;
vector<int> link;

int calculateDiff() {
  int diff = 0;
  for (int i = 0; i < start.size(); ++i) {
    for (int j = i + 1; j < start.size(); ++j) {
      diff += s[start[i]][start[j]] + s[start[j]][start[i]];
      diff -= s[link[i]][link[j]] + s[link[j]][link[i]];
    }
  }

  return abs(diff);
}

void backtrack(int idx) {
  if (start.size() == n / 2) {
    link.clear();
    int si = 0;
    for (int i = 0; i < n; ++i) {
      if (si < n / 2 && start[si] == i) si++;
      else link.push_back(i);
    }

    int cur = calculateDiff();
    ans = cur < ans ? cur : ans;

    return;
  }

  for (int i = idx; i < n; ++i) {
    start.push_back(i);
    backtrack(i + 1);
    start.pop_back();
  }
}

int main() {
  ios::sync_with_stdio(false);

  cin >> n;
  s = new int*[n];
  for (int i = 0; i < n; ++i) {
    s[i] = new int[n];
    for (int j = 0; j < n; ++j) cin >> s[i][j];
  }

  start.push_back(0);
  backtrack(1);

  cout << ans << endl;

  for (int i = 0; i < n; ++i) delete[] s[i];
  delete[] s;
}