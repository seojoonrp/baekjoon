#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool compare(pair<int, int> x, pair<int, int> y)
{
  return x.first < y.first;
}

int lis(vector<int> a)
{
  vector<int> dp;
  for (int i = 0; i < a.size(); ++i)
  {
    auto it = lower_bound(dp.begin(), dp.end(), a[i]);

    if (it == dp.end())
      dp.push_back(a[i]);
    else
      *it = a[i];
  }

  return dp.size();
}

int main()
{
  int n;
  vector<pair<int, int>> a;

  cin >> n;
  for (int i = 0; i < n; ++i)
  {
    pair<int, int> temp;
    cin >> temp.first;
    cin >> temp.second;
    a.push_back(temp);
  }

  sort(a.begin(), a.end(), compare);

  vector<int> b;
  for (int i = 0; i < n; ++i)
    b.push_back(a[i].second);

  cout << n - lis(b) << endl;
}