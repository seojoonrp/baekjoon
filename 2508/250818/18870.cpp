#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n;
  cin >> n;

  vector<int> vec(n);
  for (auto& x : vec) cin >> x;

  vector<int> sorted(vec);
  sort(sorted.begin(), sorted.end());
  sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());

  for (auto& x : vec) {
    auto dist = lower_bound(sorted.begin(), sorted.end(), x);
    cout << distance(sorted.begin(), dist) << ' ';
  }
  cout << '\n';
}