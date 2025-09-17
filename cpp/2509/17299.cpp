#include <iostream>
#include <stack>
using namespace std;

int n;
int cnt[1000001], arr[1000001];
int ans[1000001];
stack<pair<int, int>> st; // { 숫자, 인덱스 }

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
    cnt[arr[i]]++;
  }

  for (int i = 0; i < n; ++i) {
    while (!st.empty()) {
      auto cur = st.top();

      if (cur.first >= cnt[arr[i]]) break;

      ans[cur.second] = arr[i];
      st.pop();
    }
    
    st.push({ cnt[arr[i]], i });
  }

  while (!st.empty()) {
    ans[st.top().second] = -1;
    st.pop();
  }

  for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
  cout << '\n';
}