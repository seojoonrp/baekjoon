#include <iostream>
using namespace std;

int a[1025][1025];
int asum[1026][1026];

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n, m;
  cin >> n >> m;

  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
      cin >> a[i][j];
  }

  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= n; ++j)
    {
      asum[i][j] = asum[i - 1][j] + asum[i][j - 1] - asum[i - 1][j - 1] + a[i - 1][j - 1];
    }
  }

  for (int i = 0; i < m; ++i)
  {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    cout << asum[x2][y2] - asum[x1 - 1][y2] - asum[x2][y1 - 1] + asum[x1 - 1][y1 - 1] << "\n";
  }
}