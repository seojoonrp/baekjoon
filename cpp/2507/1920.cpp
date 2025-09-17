#include <iostream>
#include <algorithm>
using namespace std;

int n, m;
int a[100002];

bool binarySearch(int s, int e, int x)
{
  while (s <= e)
  {
    int m = (s + e) / 2;
    if (a[m] == x)
      return true;
    else if (a[m] < x)
      s = m + 1;
    else
      e = m - 1;
  }

  return false;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i];

  sort(a, a + n);

  cin >> m;
  for (int i = 0; i < m; ++i)
  {
    int x;
    cin >> x;

    cout << binarySearch(0, n - 1, x) << "\n";
  }
}