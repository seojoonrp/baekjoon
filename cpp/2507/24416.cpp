#include <iostream>
#include <vector>
using namespace std;

int fib_rec(int n) {
  if (n == 1 || n == 2) return 1;
  else return fib_rec(n - 1) + fib_rec(n - 2);
}

int fib_dyn(int n) {
  int ans = 0;

  vector<int> f;
  f.push_back(1);
  f.push_back(1);
  for (int i = 3; i <= n; ++i) {
    f.push_back(f[f.size() - 1] + f[f.size() - 2]);
    ans++;
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(false);

  int n;
  cin >> n;

  int rec = fib_rec(n);
  int dyn = fib_dyn(n);

  cout << rec << " " << dyn << endl;
}