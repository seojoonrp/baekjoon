#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int WEIGHT_MAX = 10002;

struct Stuff {
  int weight;
  int value;
};

int n, m;
vector<Stuff> stuffs;
int dp[2][WEIGHT_MAX];

void handle_stuff(int weight, int value, int count) {
  int cnt = 1;

  while (true) {
    if (cnt * 2 > count) {
      int left_cnt = count - (cnt - 1);
      stuffs.push_back({ weight * left_cnt, value * left_cnt });
      break;
    }

    stuffs.push_back({ weight * cnt, value * cnt });

    cnt *= 2;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    int w, v, c;
    cin >> w >> v >> c;
    handle_stuff(w, v, c);
  }

  for (Stuff& stuff : stuffs) {
    for (int j = 0; j <= m; j++) {
      dp[1][j] = dp[0][j];
      if (j - stuff.weight >= 0) {
        dp[1][j] = max(dp[1][j], dp[0][j - stuff.weight] + stuff.value);
      }
    }

    for (int j = 0; j <= m; j++) {
      dp[0][j] = dp[1][j];
    }
  }

  cout << dp[0][m] << '\n';
}