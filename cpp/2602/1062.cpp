#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int CHAR = 21;
const int MAX = 51;

int n, k;
int bits[MAX];
int ans;

int char_idx(char c) {
  if (c > 't') return c - 'a' - 5;
  else if (c > 'n') return c - 'a' - 4;
  else if (c > 'i') return c - 'a' - 3;
  else if (c > 'c') return c - 'a' - 2;
  else return c - 'a' - 1;
}

bool is_special(char c) {
  return 
    c != 'a' &&
    c != 'c' &&
    c != 'i' &&
    c != 'n' &&
    c != 't';
}

void update_ans(int state) {
  int cur_ans = 0;
  for (int i = 0; i < n; i++) {
    if ((state | bits[i]) == state) cur_ans++;
  }
  ans = max(ans, cur_ans);
}

void backtrack(int state, int last, int cnt) {
  if (cnt == k - 5) {
    update_ans(state);
    return;
  }

  for (int i = last + 1; i < CHAR; i++) {
    backtrack(state | (1 << i), i, cnt + 1);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> k;

  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    int cur_bit = 0;

    for (char c : s) {
      if (is_special(c)) {
        cur_bit |= 1 << char_idx(c);
      }
    }

    bits[i] = cur_bit;
  }

  if (k < 5) {
    cout << 0 << '\n';
    return 0;
  }

  backtrack(0, -1, 0);

  cout << ans << '\n';
}