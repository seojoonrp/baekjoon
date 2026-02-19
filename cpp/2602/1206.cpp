#include <iostream>
using namespace std;

const int MAX = 55;

bool is_div(int x, int n) {
  if ((x * n) % 1000 == 0) return true;
  
  int l = x * n;
  int r = (x + 1) * n;

  return (int)((l + 999) / 1000) * 1000 < r;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  int avg3[MAX];

  cin >> n;
  for (int i = 0; i < n; i++) {
    double d; cin >> d;
    avg3[i] = (int)(d * 1000 + 0.5);
  }

  int ans = 1;
  while (true) {
    bool flag = true;
    for (int i = 0; i < n; i++) {
      if (!is_div(avg3[i], ans)) {
        flag = false;
        break;
      } 
    }

    if (flag) break;
    ans++;
  }

  cout << ans << '\n';
}