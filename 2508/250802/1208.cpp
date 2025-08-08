#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, s;
int arr[42];
vector<int> a, b;
long long ans;

void calculate_a(int cursum, int idx) {
  if (idx > n / 2) return;

  cursum += arr[idx];
  if (cursum == s) ans++;

  a.push_back(cursum);

  calculate_a(cursum, idx + 1);
  calculate_a(cursum - arr[idx], idx + 1);
}

void calculate_b(int cursum, int idx) {
  if (idx >= n) return;

  cursum += arr[idx];
  if (cursum == s) ans++;

  b.push_back(cursum);

  calculate_b(cursum, idx + 1);
  calculate_b(cursum - arr[idx], idx + 1);
}

void calculate_cross() {
  sort(b.begin(), b.end());

  for (auto& x : a) {
    int obj = s - x;
    int cnt = upper_bound(b.begin(), b.end(), obj) - lower_bound(b.begin(), b.end(), obj);
    ans += cnt;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> s;
  for (int i = 0; i < n; ++i) cin >> arr[i];

  calculate_a(0, 0);
  calculate_b(0, n / 2 + 1);

  calculate_cross();

  cout << ans << "\n";
}