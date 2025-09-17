#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
  int n;
  int a[1002];
  vector<int> lis;

  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i];

  for (int i = 0; i < n; ++i)
  {
    auto idx = lower_bound(lis.begin(), lis.end(), a[i]);

    if (idx == lis.end())
    {
      lis.push_back(a[i]);
    }
    else
    {
      *idx = a[i];
    }
  }

  cout << lis.size() << endl;
}