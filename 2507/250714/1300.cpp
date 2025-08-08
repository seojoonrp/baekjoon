#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;
typedef long long LL;

LL n, k;

int main()
{
  cin >> n >> k;

  LL lower = 1;
  LL upper = n * n;
  LL mid;

  while (lower < upper)
  {
    mid = (lower + upper) / 2;

    LL curIdx = 0; // mid보다 작거나 같은 숫자의 개수
    for (int i = 1; i <= n; ++i)
      curIdx += min((mid / i), n);

    if (k > curIdx)
    {
      lower = mid + 1;
    }
    else
    {
      upper = mid;
    }
  }

  cout << upper << "\n";
}

// 1 2 2 3 3 4 4 4 5 5 6 6 6 6 8 8 9 10 10 12 12 12 12 15 15 16 18 18 20 20 24 24 25 30 30 36