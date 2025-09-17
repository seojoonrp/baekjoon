#include <iostream>
#include <vector>
using namespace std;

int n;
int a[1000002];
vector<int> lis;

int findLowerBoundIdx(const vector<int> &a, int x)
{
  int l = a.size();
  int start = 0;
  int end = l;
  int mid;

  while (start < end)
  {
    mid = (start + end) / 2;

    if (a[mid] >= x)
      end = mid;
    else
      start = mid + 1;
  }

  return end;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i];

  lis.push_back(a[0]);
  for (int i = 1; i < n; ++i)
  {
    int ub = findLowerBoundIdx(lis, a[i]);

    if (ub == lis.size())
      lis.push_back(a[i]);
    else
      lis[ub] = a[i];
  }

  cout << lis.size() << "\n";
}