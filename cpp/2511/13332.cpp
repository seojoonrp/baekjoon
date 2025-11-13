#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9;
const int N = 102, M = 102;

struct Vacation {
  int cond;
  int lo, up;
};

int n, m;
int people_lo, people_up;
int day_lo[N], day_up[N];
vector<Vacation> vacations[M];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> m >> n;
  cin >> people_lo >> people_up;

  for (int i = 1; i <= n; i++) {
    cin >> day_lo[i] >> day_up[i];
  }

  for (int i = 1; i <= m; i++) {
    int vac_cnt;
    cin >> vac_cnt;
    vacations[i].resize(vac_cnt);

    for (int j = 0; j < vac_cnt; j++) {
      Vacation& vac = vacations[i][j];
      cin >> vac.cond >> vac.lo >> vac.up;
    }
  }
}