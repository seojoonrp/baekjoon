#include <iostream>
using namespace std;

int main()
{
  long long a, b, c;
  cin >> a >> b >> c;
  a %= c;

  long long ans = 1;
  while (b > 0)
  {
    if (b % 2 == 1)
      ans = (ans * a) % c;

    a = (a * a) % c;
    b /= 2;
  }

  cout << ans << endl;
}