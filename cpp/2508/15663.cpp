#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
int arr[10];
bool visited[10];

void backtrack(vector<int>& res) {
  if (res.size() == m) {
    for (auto& idx : res) cout << arr[idx] << " ";
    cout << "\n";
    
    return;
  }

  int prevnum = -1;
  for (int i = 0; i < n; ++i) {
    if (!visited[i] && arr[i] != prevnum) {      
      visited[i] = true;
      res.push_back(i);

      backtrack(res);

      visited[i] = false;
      res.pop_back();

      prevnum = arr[i];
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> m;
  for (int i = 0; i < n; ++i) cin >> arr[i];

  sort(arr, arr + n);

  vector<int> result;
  backtrack(result);
}