#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<int, int>> pq;
int board[1502][1502];
int idx[1502];

bool priority(const pair<int, int> &a, const pair<int, int> &b) { return a.first > b.first; }

void pq_insert(const pair<int, int> &x)
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

pair<int, int> pq_delete()
{
  pair<int, int> res = pq[0];
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

  return res;
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
    for (int j = 0; j < n; ++j)
      cin >> board[i][j];
  }

  for (int i = 0; i < n; ++i)
  {
    pair<int, int> x;
    x.first = board[n - 1][i];
    x.second = i;
    pq_insert(x);
    idx[i] = n - 1;
  }

  for (int i = 0; i < n - 1; ++i)
  {
    int curMaxIdx = pq_delete().second;
    pair<int, int> x;
    x.first = board[--idx[curMaxIdx]][curMaxIdx];
    x.second = curMaxIdx;
    pq_insert(x);
  }

  cout << pq_delete().first << "\n";
}