#include <iostream>
using namespace std;

int modsum[1002];

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n, m;
  cin >> n >> m;

  long long ans = 0;
  int cursum = 0;
  modsum[0] = 1;

  for (int i = 0; i < n; ++i)
  {
    int x;
    cin >> x;

    cursum = (cursum + x) % m;

    ans += modsum[cursum];
    modsum[cursum]++;
  }

  cout << ans << endl;
}