#include <iostream>
using namespace std;

int n, k;
int value[12];

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> k;
  for (int i = 0; i < n; ++i)
    cin >> value[i];

  int ans = 0;
  for (int i = n - 1; i >= 0; --i)
  {
    int inject = k / value[i];

    ans += inject;
    k %= value[i];

    if (k == 0)
      break;
  }

  cout << ans << endl;
}