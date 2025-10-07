#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Line {
  int left, right;
};

bool compare_line(const Line& l1, const Line& l2) {
  if (l1.left == l2.left) return l1.right > l2.right;
  return l1.left < l2.left;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;
  
  vector<Line> lines(n);
  for (int i = 0; i < n; i++) {
    cin >> lines[i].left >> lines[i].right;
  }

  sort(lines.begin(), lines.end(), compare_line);

  int ans = 0;
  int lo = lines[0].left;
  int hi = lines[0].right;

  for (int i = 1; i < n; i++) {
    Line line = lines[i];

    if (line.right <= hi) continue;

    if (line.left <= hi) hi = line.right;
    else {
      ans += hi - lo;
      lo = line.left;
      hi = line.right;
    }
  }
  ans += hi - lo;

  cout << ans << '\n';
}