#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  int n;
  cin >> n;

  vector<pair<int, int>> a(n); //{값, 원래 인덱스}
  vector<int> ans(n);

  for (int i = 0; i < n; ++i) {
    cin >> a[i].first;
    a[i].second = i;
  }

  sort(a.begin(), a.end());

  for (int i = 0; i < n; ++i) {
    ans[a[i].second] = i;
  }

  for (int i = 0; i < n; ++i) {
    cout << ans[i] << " ";
  }
}