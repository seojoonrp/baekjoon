#include <iostream>
using namespace std;

int s, n, k, margin;
int r1, r2, c1, c2;

int solve(int r, int c, int t) {
  if (t == 0) return 0;

  int pr = r / n;
  int pc = c / n;

  int past = solve(pr, pc, t - 1);
  if (past == 1) return 1;
  else {
    int rr = r % n;
    int rc = c % n;

    if (rr >= margin && rr < margin + k && rc >= margin && rc < margin + k) {
      return 1;
    } else {
      return 0;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> s >> n >> k;
  cin >> r1 >> r2 >> c1 >> c2;
  margin = (n - k) / 2;

  for (int r = r1; r <= r2; r++) {
    for (int c = c1; c <= c2; c++) {
      cout << solve(r, c, s);
    }
    cout << '\n';
  }
}