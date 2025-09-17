#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
  string a, b;
  cin >> a >> b;

  int lenA = a.length();
  int lenB = b.length();

  int dp[1002][1002] = {};

  for (int i = 1; i <= lenA; ++i)
  {
    for (int j = 1; j <= lenB; ++j)
    {
      if (a[i - 1] == b[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      else
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    }
  }

  cout << dp[lenA][lenB] << endl;
}