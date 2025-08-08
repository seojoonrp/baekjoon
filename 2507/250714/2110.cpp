#include <iostream>
#include <algorithm>
using namespace std;

int n, c;
int x[200002];

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> c;
  for (int i = 0; i < n; ++i)
    cin >> x[i];

  sort(x, x + n);

  int lower = 1;
  int upper = x[n - 1] - x[0];
  int mid;
  int ans = -1;

  while (lower <= upper)
  {
    mid = (lower + upper) / 2;

    bool possible = false;
    int curCoord = x[0];
    int curRouters = 1;
    for (int i = 1; i < n; ++i)
    {
      if (curCoord + mid <= x[i])
      {
        curCoord = x[i];
        curRouters++;
      }

      if (curRouters == c)
      {
        possible = true;
        break;
      }
    }

    if (possible)
    {
      lower = mid + 1;
      if (ans < mid)
        ans = mid;
    }
    else
      upper = mid - 1;
  }

  cout << ans << "\n";
}