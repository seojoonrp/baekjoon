#include <iostream>
#include <algorithm>
using namespace std;

int n, m;
int tree[1000002];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int lower = 0;
  int upper = 0;
  int ans = 0;

  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    cin >> tree[i];
    upper = max(upper, tree[i]);
  }

  long cursum;

  while (lower <= upper) {
    int mid = (lower + upper) / 2;

    cursum = 0;
    for (int i = 0; i < n; ++i) {
      if (tree[i] > mid) cursum += (tree[i] - mid);
    }

    if (cursum >= m) {
      ans = mid;
      lower = mid + 1;
    } else {
      upper = mid - 1;
    }
  }

  cout << ans << '\n';
}