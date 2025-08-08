#include <iostream>
#include <string>
using namespace std;

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  string s;
  int m;

  cin >> s;
  cin >> m;

  int l = s.length();
  int dp[1003][26];

  for (int i = 1; i <= l; ++i)
  {
    for (int j = 0; j < 26; ++j)
    {
      if (s[i - 1] - 'a' == j)
        dp[i][j] = dp[i - 1][j] + 1;
      else
        dp[i][j] = dp[i - 1][j];
    }
  }

  // for (int i = 1; i <= l; ++i)
  // {
  //   for (int j = 0; j < 26; ++j)
  //     cout << dp[i][j] << " ";
  //   cout << endl;
  // }

  for (int i = 0; i < m; ++i)
  {
    char c;
    int l, r;
    cin >> c >> l >> r;

    cout << dp[r + 1][c - 'a'] - dp[l][c - 'a'] << "\n";
  }
}