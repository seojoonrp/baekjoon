#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

vector<int> pq;

bool priority(int a, int b)
{
  if (abs(a) != abs(b))
    return abs(a) < abs(b);
  else
    return a < b;
}

void pq_insert(int x)
{
  pq.push_back(x);

  int cur = pq.size() - 1;
  while (cur > 0)
  {
    int parent = (cur - 1) / 2;
    if (priority(pq[cur], pq[parent]))
    {
      swap(pq[cur], pq[parent]);
      cur = parent;
    }
    else
      break;
  }
}

void pq_delete(int x)
{
  if (pq.empty())
  {
    cout << 0 << "\n";
    return;
  }

  cout << pq[0] << "\n";
  pq[0] = pq[pq.size() - 1];
  pq.pop_back();

  int cur = 0;
  while (true)
  {
    int left = cur * 2 + 1;
    int right = cur * 2 + 2;
    int largest = cur;

    if (left < pq.size() && priority(pq[left], pq[largest]))
      largest = left;
    if (right < pq.size() && priority(pq[right], pq[largest]))
      largest = right;

    if (largest == cur)
      break;

    swap(pq[cur], pq[largest]);
    cur = largest;
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n;
  cin >> n;

  for (int i = 0; i < n; ++i)
  {
    int x;
    cin >> x;

    if (x != 0)
      pq_insert(x);
    else
      pq_delete(x);

    // for (int i = 0; i < pq.size(); ++i)
    //   cout << pq[i] << " ";
    // cout << "\n";
  }
}