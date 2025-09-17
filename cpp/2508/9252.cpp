#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
  int lcs;
  char came_from; // a, b, d
  char letter_added;
};

string a, b;
int na, nb;
Node dp[1003][1003]; // a의 i번째, b의 j번째까지 고려했을 때 LCS 길이
string lcs;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> a >> b;
  na = a.length();
  nb = b.length();

  bool flag = false;
  for (int i = 0; i < na; ++i) {
    if (flag) dp[i][0] = { 1, 'a', '_' };
    else if (a[i] == b[0]) {
      flag = true;
      dp[i][0] = { 1, 'a', a[i] };
    } else {
      dp[i][0] = { 0, 'a', '_' };
    }
  }
  flag = false;
  for (int j = 0; j < nb; ++j) {
    if (flag) dp[0][j] = { 1, 'b', '_' };
    else if (b[j] == a[0]) {
      flag = true;
      dp[0][j] = { 1, 'b', b[j] };
    } else {
      dp[0][j] = { 0, 'b', '_' };
    }
  }

  for (int i = 1; i < na; ++i) {
    for (int j = 1; j < nb; ++j) {
      if (a[i] == b[j]) {
        dp[i][j].lcs = dp[i - 1][j - 1].lcs + 1;
        dp[i][j].came_from = 'd';
        dp[i][j].letter_added = a[i];
      } else {
        dp[i][j].letter_added = '_';
        if (dp[i - 1][j].lcs > dp[i][j - 1].lcs) {
          dp[i][j].lcs = dp[i - 1][j].lcs;
          dp[i][j].came_from = 'a';
        } else {
          dp[i][j].lcs = dp[i][j - 1].lcs;
          dp[i][j].came_from = 'b';
        }
      }
    }
  }

  cout << dp[na - 1][nb - 1].lcs << "\n";

  if (dp[na - 1][nb - 1].lcs == 0) return 0;

  int xa = na - 1;
  int xb = nb - 1;
  while (xa >= 0 && xb >= 0 && dp[xa][xb].lcs != 0) {
    Node cur = dp[xa][xb];
    
    if (cur.came_from == 'a') xa--;
    else if (cur.came_from == 'b') xb--;
    else {
      xa--;
      xb--;
    }

    if (cur.letter_added != '_') lcs += cur.letter_added;
  }

  reverse(lcs.begin(), lcs.end());

  cout << lcs << "\n";
}