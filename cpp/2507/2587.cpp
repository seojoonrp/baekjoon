#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
  int a[5];
  for (int i = 0; i < 5; ++i)
    cin >> a[i];

  sort(a, a + 5);

  int avg = 0;
  for (int i = 0; i < 5; ++i)
    avg += a[i] / 5;
  cout << avg << endl
       << a[2] << endl;
}