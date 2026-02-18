#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int ALP = 26;
const int INF = 1e9;

vector<string> words;

bool is_in(string& a, string& b) {
  int b_idx = 0;
  for (char ac : a) {
    bool found = false;
    while (b_idx < (int)b.size()) {
      if (ac == b[b_idx]) {
        found = true;
        b_idx++;
        break;
      }
      if (ac < b[b_idx]) return false;
      b_idx++;
    }
    if (!found) return false;
  }
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  while (true) {
    string word; cin >> word;
    if (word == "-") break;

    sort(word.begin(), word.end());
    words.push_back(word);
  }

  while (true) {
    string board; cin >> board;
    if (board == "#") break;

    bool in_board[ALP] = {};
    for (char c : board) in_board[c - 'A'] = true;

    sort(board.begin(), board.end());
    int cnt[ALP] = {};

    for (string& word : words) {
      if (is_in(word, board)) {
        for (int i = 0; i < (int)word.size(); i++) {
          if (i > 0 && word[i - 1] == word[i]) continue;
          cnt[word[i] - 'A']++;
        }
      }
    }

    string ans_min = "", ans_max = "";
    int cnt_min = INF, cnt_max = -1;
    for (int i = 0; i < ALP; i++) {
      if (!in_board[i]) continue;
      int cur = cnt[i];

      if (cur < cnt_min) {
        cnt_min = cur;
        ans_min = (char)(i + 'A');
      } else if (cur == cnt_min) {
          ans_min += (char)(i + 'A');
      }

      if (cur > cnt_max) {
        cnt_max = cur;
        ans_max = (char)(i + 'A');
      } else if (cur == cnt_max) {
        ans_max += (char)(i + 'A');
      }
    }

    cout << ans_min << ' ' << cnt_min << ' ';
    cout << ans_max << ' ' << cnt_max << '\n';
  }
}