#include <iostream>
#include <queue>
using namespace std;
using ll = long long;

int n;
priority_queue<ll, vector<ll>, greater<>> pq;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tc;
  cin >> tc;
  while (tc--) {
    ll ans = 0;

    cin >> n;
    for (int i = 0; i < n; ++i) {
      int x;
      cin >> x;
      pq.push(x);
    }

    while (pq.size() > 1) {
      ll file1 = pq.top();
      pq.pop();
      ll file2 = pq.top();
      pq.pop();
      
      ans += file1 + file2;
      pq.push(file1 + file2);
    }

    cout << ans << '\n';
    pq.pop();
  }
}