#include <iostream>
using namespace std;

int n, m, k;
int a[102][102], b[102][102];

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> m;
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < m; ++j)
      cin >> a[i][j];
  }
  cin >> m >> k;
  for (int i = 0; i < m; ++i)
  {
    for (int j = 0; j < k; ++j)
      cin >> b[i][j];
  }

  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < k; ++j)
    {
      int cur = 0;
      for (int x = 0; x < m; ++x)
        cur += a[i][x] * b[x][j];

      cout << cur << " ";
    }
    cout << "\n";
  }
}