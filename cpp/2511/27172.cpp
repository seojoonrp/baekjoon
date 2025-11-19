#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int N_MAX = 100001;
const int X_MAX = 1000001;

int n;
int arr[N_MAX];
bool in_game[X_MAX];
int score[X_MAX];

void calc_divisors(int x) {
  for (int i = 1; i <= (int)sqrt(x); i++) {
    if (x % i == 0) {
      if (in_game[i]) {
        score[i]++;
        score[x]--;
      }
      if (in_game[x / i] && (i * i != x)) {
        score[x / i]++;
        score[x]--;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
    in_game[arr[i]] = true;
  }

  for (int i = 0; i < n; i++) {
    calc_divisors(arr[i]);
  }

  for (int i = 0; i < n; i++) {
    cout << score[arr[i]] << ' ';
  }
  cout << '\n';
}