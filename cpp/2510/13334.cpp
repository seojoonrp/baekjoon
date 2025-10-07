#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
using ll = long long;

struct Line {
  ll left;
  ll right;
};

struct LinePriority {
  bool operator()(const Line& l1, const Line& l2) const {
    return l1.left > l2.left;
  }
};

bool compare_line(const Line& l1, const Line& l2) {
  if (l1.right == l2.right) return l1.left < l2.left;
  return l1.right < l2.right;
}

int n;
ll d;
vector<Line> lines;
priority_queue<Line, vector<Line>, LinePriority> pq;

int solve() {
  int ans = -1;

  ll cur_right;
  for (Line& line : lines) {
    cur_right = line.right;
    ll left_bound = cur_right - d;
    pq.push(line);

    while (!pq.empty()) {
      Line cur_top = pq.top();
      if (cur_top.left < left_bound) pq.pop();
      else break;
    }

    ans = max(ans, static_cast<int>(pq.size()));
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++) {
    ll a, b;
    cin >> a >> b;
    if (a > b) swap(a, b);
    lines.push_back({ a, b });
  }
  cin >> d;

  sort(lines.begin(), lines.end(), compare_line);

  cout << solve() << '\n';
}