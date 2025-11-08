#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> arr;

void solve(vector<int>& vec, int cur_idx) {
  if ((int)vec.size() == m) {
    for (int& x : vec) cout << x << ' ';
    cout << '\n';
    return;
  }

  for (int i = cur_idx; i < n; i++) {
    vec.push_back(arr[i]);
    solve(vec, i);
    vec.pop_back();
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    arr.push_back(x);
  }

  sort(arr.begin(), arr.end());
  arr.erase(unique(arr.begin(), arr.end()), arr.end());
  n = (int)arr.size();

  vector<int> vec;
  solve(vec, 0);
}