#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

int n, d;
int rock[100001];
deque<pair<int, long long>> dq;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> d;
  for (int i = 0; i < n; ++i) {
    cin >> rock[i];
  }

  long long ans = rock[0];
  for (int i = 0; i < n; ++i) {
    long long cur_score = rock[i];

    while (!dq.empty() && dq.front().first < i - d) dq.pop_front();

    if (!dq.empty()) {
      cur_score = max(cur_score, dq.front().second + rock[i]);
    }

    while (!dq.empty() && dq.back().second <= cur_score) dq.pop_back();

    ans = max(ans, cur_score);
    dq.push_back({ i, cur_score });
  }

  cout << ans << '\n';
}