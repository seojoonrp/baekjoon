#include <iostream>
using namespace std;

int main()
{
  int n, k, p;
  cin >> n >> k;
  p = 1000000007;

  long long kfac = 1;
  for (int i = 2; i <= k; ++i)
    kfac = (kfac * i) % p;

  long long ans = 1;
  int exp = p - 2;
  while (exp > 0)
  {
    if (exp % 2 == 1)
      ans = (ans * kfac) % p;

    kfac = (kfac * kfac) % p;
    exp /= 2;
  }

  for (int i = n; i > n - k; --i)
    ans = (ans * i) % p;

  cout << ans << endl;
}