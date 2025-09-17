#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, m;
vector<int> arr, ans;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    arr.push_back(x);
  }
  
  sort(arr.begin(), arr.end());

  cin >> m;
  while (m--) {
    int x;
    cin >> x;

    int num = upper_bound(arr.begin(), arr.end(), x) - lower_bound(arr.begin(), arr.end(), x);
    ans.push_back(num);
  }

  for (auto& x : ans) cout << x << ' ';
  cout << '\n';
}