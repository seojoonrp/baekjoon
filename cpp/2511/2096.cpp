#include <iostream>
#include <algorithm>
using namespace std;

int n;
int min_[2][3];
int max_[2][3];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;

  for (int i = 0; i < 3; i++) {
    cin >> min_[0][i];
    max_[0][i] = min_[0][i];
  }

  for (int i = 1; i < n; i++) {
    for (int j = 0; j < 3; j++) {
      cin >> min_[1][j];
      max_[1][j] = min_[1][j];
    }

    min_[1][0] += min(min_[0][0], min_[0][1]);
    min_[1][1] += min({ min_[0][0], min_[0][1], min_[0][2] });
    min_[1][2] += min(min_[0][1], min_[0][2]);

    max_[1][0] += max(max_[0][0], max_[0][1]);
    max_[1][1] += max({ max_[0][0], max_[0][1], max_[0][2] });
    max_[1][2] += max(max_[0][1], max_[0][2]);

    for (int j = 0; j < 3; j++) {
      min_[0][j] = min_[1][j];
      max_[0][j] = max_[1][j];
    }
  }

  cout << max({ max_[0][0], max_[0][1], max_[0][2] }) << ' ';
  cout << min({ min_[0][0], min_[0][1], min_[0][2] }) << '\n';
}