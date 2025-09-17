#include <iostream>
#include <stack>
using namespace std;

int n;
int ans[1000001];
stack<pair<int, int>> st; // { 숫자, 인덱스 }

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;

    while (!st.empty()) {
      auto cur = st.top();

      if (cur.first >= x) break;

      ans[cur.second] = x;
      st.pop();
    }
    
    st.push({ x, i });
  }

  while (!st.empty()) {
    ans[st.top().second] = -1;
    st.pop();
  }

  for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
  cout << '\n';
}