#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;
using ll = long long;

int n;
stack<int> st;
int stick[100001];
ll ans;

void pop_and_calc(int next) {
  int cur = st.top();
  st.pop();

  ll cur_area;
  if (st.empty()) {
    cur_area = (ll)stick[cur] * next;
  } else {
    int prev = st.top();
    cur_area = (ll)stick[cur] * (next - prev - 1);
  }

  ans = max(ans, cur_area);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; ++i) cin >> stick[i];

  st.push(0);
  for (int i = 1; i <= n; ++i) {
    while (!st.empty() && stick[st.top()] > stick[i]) {
      pop_and_calc(i);
    }
    st.push(i);
  }

  cout << ans << '\n';
}