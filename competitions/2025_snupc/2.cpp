#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

int dice[5];
bool visited[5];

int final_ans = -1;

int score() {
  int dice_cnt[7] = {};
  for (int i = 0; i < 5; ++i) {
    dice_cnt[dice[i]]++;
  }

  int ans = 0;
  for (int i = 1; i <= 6; ++i) {
    if (dice_cnt[i] == 5) return 50;
    ans = max(ans, dice_cnt[i] * i);
  }

  return ans;
}

void func(vector<int>& vec, int cnt) {
  // for (auto& x : vec) cout << x << ' ';
  // cout << '\n';

  if (vec.size() == cnt) {
    int temp_ans = 0;

    int temp_dice[5] = {};
    for (int i = 0; i < 5; ++i) temp_dice[i] = dice[i];

    for (int i = 0; i < pow(6, cnt); ++i) {
      vector<int> digit = {};
      int temp = i;
      while (digit.size() < cnt) {
        digit.push_back(temp % 6);
        temp /= 6;
      }
      reverse(digit.begin(), digit.end());

      for (int j = 0; j < cnt; ++j) {
        dice[vec[j]] = digit[j] + 1;
      }
      temp_ans +=score();
      // cout <<"tempans"<< temp_ans << '\n';
    }
    temp_ans *= pow(6, 5 - cnt);

    final_ans = max(final_ans, temp_ans);
    for (int i = 0; i < 5; ++i) dice[i] = temp_dice[i];

    return;
  }

  int l = vec[vec.size() - 1];
  for (int i = l + 1; i < 5; ++i) {
    vec.push_back(i);
    func(vec, cnt);
    vec.pop_back();
  }
}

void solve(int cnt) {
  if (cnt == 0) final_ans = score() * 6 * 6 * 6 * 6 * 6;
  else {
    vector<int> vec = {};
    for (int i = 0; i < 5; ++i) {
      vec.push_back(i);
      func(vec, cnt);
      vec.pop_back();
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  for (int i = 0; i < 5; ++i) {
    cin >> dice[i];
  }

  for (int i = 0; i <= 5; ++i) solve(i);
  // solve(0);
  // solve(1);

  cout << final_ans << '\n';
}