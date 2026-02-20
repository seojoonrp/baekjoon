#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 9;

int n;
int arr[MAX];
int ans = 0;
bool visited[MAX];

void update_ans(vector<int>& vec) {
  int s[MAX] = {};
  for (int i = 1; i <= n; i++) {
    s[i] = s[i - 1] + arr[vec[i - 1]];
  }

  int cur_ans = 0;
  for (int i = 1; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (s[j] - s[i - 1] == 50) cur_ans++;
    }
  }

  ans = max(ans, cur_ans);
}

void backtrack(vector<int>& vec) {
  if ((int)vec.size() == n) {
    update_ans(vec);
    return;
  }

  for (int i = 2; i <= n; i++) {
    if (!visited[i]) {
      visited[i] = true;
      vec.push_back(i);

      backtrack(vec);

      visited[i] = false;
      vec.pop_back();
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> arr[i];

  vector<int> vec;
  vec.push_back(1);
  visited[1] = true;
  backtrack(vec);

  cout << ans << '\n';
}