#include <iostream>
#include <algorithm>
using namespace std;

int n;
pair<int, int> a[100002];

bool compare(pair<int, int> x, pair<int, int> y)
{
  if (x.second != y.second)
    return x.second < y.second;
  return x.first < y.first;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i].first >> a[i].second;

  sort(a, a + n, compare);

  // for (int i = 0; i < n; ++i)
  //   cout << a[i].first << " " << a[i].second << endl;

  int curend = -1;
  int ans = 0;
  for (int i = 0; i < n; ++i)
  {
    if (a[i].first >= curend)
    {
      curend = a[i].second;
      ans++;
    }
  }

  cout << ans << endl;
}