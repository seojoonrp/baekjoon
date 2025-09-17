#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int n, m;
string arr[500002];
vector<string> ans;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> m;
  for (int i = 0; i < n; ++i) cin >> arr[i];
  sort(arr, arr + n);

  while (m--) {
    string s;
    cin >> s;

    bool isFound = binary_search(arr, arr + n, s);
    if (isFound) ans.push_back(s);
  }

  sort(ans.begin(), ans.end());
  cout << ans.size() << '\n';
  for (auto& s : ans) cout << s << '\n';
}