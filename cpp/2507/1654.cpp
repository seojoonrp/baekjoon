#include <iostream>
#include <algorithm>
using namespace std;

int n, k;
int stick[10002];

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> k >> n;
  for (int i = 0; i < k; ++i)
    cin >> stick[i];

  long long start = 1;
  long long end = *max_element(stick, stick + k);
  long long mid;
  long long ans = 0;

  while (start <= end)
  {
    mid = (start + end) / 2;

    int curnum = 0;
    for (int i = 0; i < k; ++i)
      curnum += (stick[i] / mid);

    if (curnum >= n)
    {
      start = mid + 1;
      if (ans < mid)
        ans = mid;
    }
    else
      end = mid - 1;
  }

  cout << ans << endl;
}