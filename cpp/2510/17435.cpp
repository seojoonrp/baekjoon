#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_M = 200001;
const int MAX_LN = 19;

int m;
int func[MAX_M];
int jump[MAX_LN][MAX_M]; // jump[i][j] = f^(2^i)[j]

void fill_jump() {
  for (int i = 1; i <= m; i++) jump[0][i] = func[i];

  for (int i = 1; i < MAX_LN; i++) {
    for (int j = 1; j <= m; j++) {
      jump[i][j] = jump[i - 1][jump[i - 1][j]];
    }
  }
}

int solve(int n, int x) {
  for (int i = 0; i < MAX_LN; i++) {
    if ((1 << i) & n) x = jump[i][x];
  }

  return x;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> m;
  for (int i = 1; i <= m; i++) cin >> func[i];

  fill_jump();

  int q;
  cin >> q;

  while (q--) {
    int n, x;
    cin >> n >> x;
    cout << solve(n, x) << '\n';
  }
}