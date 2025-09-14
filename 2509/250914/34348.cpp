#include <iostream>
#include <string>
using namespace std;

string snupc = "snupc";
int letters[5][100001];

int find_min_idx(int c, int cnt, int s, int e) {
  if (letters[c][e] - letters[c][s - 1] < cnt) return -1;

  int mid;
  int s_backup = s;

  while (s < e) {
    mid = (s + e) / 2;

    int check = letters[c][mid] - letters[c][s_backup - 1];

    if (check < cnt) {
      s = mid + 1;
    } else {
      e = mid;
    }
  }

  return e;
}

bool check(int cnt, int s, int e) {
  int cur_s = s;
  bool ret = true;
  
  for (int i = 0; i < 5; ++i) {
    int min_idx = find_min_idx(i, cnt, cur_s, e);
    if (min_idx == -1) {
      ret = false;
      break;
    }
    cur_s = min_idx + 1;
  }
  
  // cout << cnt << ' ' << s << ' ' << e << ' ' << ret << endl;
  return ret;
}

int solve(int s, int e) {
  int lo = 0;
  int hi = ((e - s) / 5) + 1;
  int mid;

  while (lo < hi) {
    mid = (lo + hi + 1) / 2;

    if (check(mid, s, e)) {
      lo = mid;
    } else {
      hi = mid - 1;
    }
  }

  return lo;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  char c;
  int l = 1;
  while (cin.get(c) && c != '\n') {
    if (c == '\n') break;
    for (int i = 0; i < 5; ++i) {
      if (c == snupc[i]) letters[i][l] = letters[i][l - 1] + 1;
      else letters[i][l] = letters[i][l - 1];
    }
    l++;
  }

  int q;
  cin >> q;

  while (q--) {
    int s, e;
    cin >> s >> e;
    cout << solve(s, e) << '\n';
  }
}