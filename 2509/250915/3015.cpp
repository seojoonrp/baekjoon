#include <iostream>
#include <stack>
using namespace std;
using ll = long long;

int n;
stack<pair<int, int>> st;
ll ans;

void custom_push(int height) {
  int equal_count = 1;
  
  while (!st.empty() && st.top().first < height) {
    ans += st.top().second;
    st.pop();
  }

  if (!st.empty()) {
    if (st.top().first == height) {
      ans += st.top().second;
      equal_count = st.top().second + 1;
      st.pop();

      if (!st.empty()) ans++;
    } else {
      ans++;
    }
  }

  st.push({ height, equal_count });
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; ++i) {
    int h;
    cin >> h;
    custom_push(h);
  }

  cout << ans << '\n';
}