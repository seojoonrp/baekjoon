#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N_MAX = 55;
const int M_MAX = 1e4 + 5;

int n, m;
int crain[N_MAX];
int box[M_MAX];
bool moved[M_MAX];
int idx[N_MAX];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++) cin >> crain[i];
  cin >> m;
  for (int i = 0; i < m; i++) cin >> box[i];

  sort(crain, crain + n, greater<>());
  sort(box, box + m, greater<>());

  if (crain[0] < box[0]) {
    cout << -1 << '\n';
    return 0;
  }

  int ans = 0;
  int move_cnt = 0;

  while (move_cnt < m) {
    for (int i = 0; i < n; i++) {
      for (int& j = idx[i]; j < m; j++) {
        if (!moved[j] && crain[i] >= box[j]) {
          moved[j] = true;
          move_cnt++;
          break;
        }
      }
    }

    ans++;
  }

  cout << ans << '\n';
}