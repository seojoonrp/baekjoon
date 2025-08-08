#include <iostream>
using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  int a[100003] = {};
  int asum[100003] = {};

  cin >> n >> m;
  for (int i = 0; i < n; ++i)
  {
    cin >> a[i];
    asum[i + 1] = asum[i] + a[i];
  }

  for (int i = 0; i < m; ++i)
  {
    int x, y;
    cin >> x >> y;
    cout << asum[y] - asum[x - 1] << "\n";
  }
}