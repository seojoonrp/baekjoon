// #6549 히스토그램에서 가장 큰 직사각형
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// 크기 n짜리 히스토그램 hist의 lower부터 upper까지(둘 다 포함) 탐색했을 때 가장 큰 직사각형의 넓이
long findLargestRect(const vector<long> &hist, int lower, int upper, const int n)
{
  // lower = upper이면, 즉 너비가 1이라면 바로 직사각형 넓이 반환
  if (lower == upper)
    return hist[lower];

  int mid = (lower + upper) / 2;

  // 왼쪽, 오른쪽 재귀 탐색
  long leftMaxRect = findLargestRect(hist, lower, mid, n);
  long rightMaxRect = findLargestRect(hist, mid + 1, upper, n);

  // 중간을 포함하는 직사각형 탐색
  long midMaxRect = hist[mid];
  long curHeight = hist[mid];
  int l = mid;
  int r = mid;

  while (lower < l && r < upper)
  {
    if (hist[l - 1] < hist[r + 1])
    {
      curHeight = min(curHeight, hist[r + 1]);
      r++;
    }
    else
    {
      curHeight = min(curHeight, hist[l - 1]);
      l--;
    }
    midMaxRect = max(midMaxRect, curHeight * (r - l + 1));
  }
  while (lower < l)
  {
    curHeight = min(curHeight, hist[l - 1]);
    l--;
    midMaxRect = max(midMaxRect, curHeight * (r - l + 1));
  }
  while (r < upper)
  {
    curHeight = min(curHeight, hist[r + 1]);
    r++;
    midMaxRect = max(midMaxRect, curHeight * (r - l + 1));
  }

  return max({leftMaxRect, rightMaxRect, midMaxRect});
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n;
  while (cin >> n && n != 0)
  {
    vector<long> hist(n);
    for (int i = 0; i < n; ++i)
      cin >> hist[i];

    cout << findLargestRect(hist, 0, n - 1, n) << "\n";
  }
}