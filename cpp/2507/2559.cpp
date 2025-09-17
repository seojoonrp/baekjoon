#include <iostream>
#include <climits>
using namespace std;

int a[100002];

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n, m;
  cin >> n >> m;

  for (int i = 0; i < n; ++i)
  {
    cin >> a[i];
  }

  int cursum = 0;
  for (int i = 0; i < m; ++i)
    cursum += a[i];

  int ans = cursum;
  for (int i = m; i < n; ++i)
  {
    cursum += a[i];
    cursum -= a[i - m];

    ans = max(ans, cursum);
  }

  cout << ans << endl;
}