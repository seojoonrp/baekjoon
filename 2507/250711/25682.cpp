#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string board[2002];
bool flip[2002][2002];
// BWBW로 만들기 위해 뒤집어야 하면 true, 아니면 false
int flipsum[2003][2003];

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 0; i < n; ++i)
    cin >> board[i];

  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < m; ++j)
    {
      if ((i + j) % 2 == 0)
      {
        if (board[i][j] == 'B')
          flip[i][j] = false;
        else
          flip[i][j] = true;
      }
      else
      {
        if (board[i][j] == 'W')
          flip[i][j] = false;
        else
          flip[i][j] = true;
      }
    }
  }

  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= m; ++j)
    {
      flipsum[i][j] = flipsum[i][j - 1] + flipsum[i - 1][j] - flipsum[i - 1][j - 1];
      flipsum[i][j] += flip[i - 1][j - 1] ? 1 : 0;
    }
  }

  int ans = k * k / 2;
  for (int i = k; i <= n; ++i)
  {
    for (int j = k; j <= m; ++j)
    {
      int temp = flipsum[i][j] - flipsum[i - k][j] - flipsum[i][j - k] + flipsum[i - k][j - k];
      ans = min({ans, temp, k * k - temp});
    }
  }

  cout << ans << endl;
}