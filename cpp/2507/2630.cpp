#include <iostream>
using namespace std;

int n;
bool board[129][129];
pair<int, int> ans;

void cut(int x, int y, int n)
{
  // cout << "cut " << x << " " << y << " " << n << " called" << endl;

  if (n == 1)
  {
    if (board[x][y])
      ans.second++;
    else
      ans.first++;
    return;
  }

  bool fucked = false;
  for (int i = x; i < x + n; ++i)
  {
    for (int j = y; j < y + n; ++j)
    {
      if (board[i][j] != board[x][y])
      {
        fucked = true;
        break;
      }
    }
  }

  if (!fucked)
  {
    if (board[x][y])
      ans.second++;
    else
      ans.first++;
    return;
  }

  cut(x, y, n / 2);
  cut(x + n / 2, y, n / 2);
  cut(x, y + n / 2, n / 2);
  cut(x + n / 2, y + n / 2, n / 2);
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
      cin >> board[i][j];
  }

  ans.first = ans.second = 0;
  cut(0, 0, n);

  cout << ans.first << endl
       << ans.second << endl;
}