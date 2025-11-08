#include <iostream>
#include <queue>
using namespace std;

struct Ans {
  int num;
  int cnt;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int a, b;
  cin >> a >> b;

  queue<Ans> q;
  q.push({ b, 1 });

  while (!q.empty()) {
    Ans cur = q.front();
    q.pop();

    int curn = cur.num;

    if (curn == a) {
      cout << cur.cnt << '\n';
      return 0;
    }

    if (curn == 0) continue;
    if (curn % 10 == 1) q.push({ curn / 10, cur.cnt + 1 });
    if (curn % 2 == 0) q.push({ curn / 2, cur.cnt + 1 });
  }

  cout << -1 << '\n';
}