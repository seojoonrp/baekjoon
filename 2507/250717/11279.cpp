#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> heap;

void heapInsert(int x)
{
  heap.push_back(x);

  int cur = heap.size() - 1;
  while (cur > 0)
  {
    int parent = (cur - 1) / 2;
    if (heap[parent] < heap[cur])
    {
      swap(heap[parent], heap[cur]);
      cur = parent;
    }
    else
      break;
  }
}

void heapDelete()
{
  if (heap.empty())
  {
    cout << 0 << "\n";
    return;
  }

  cout << heap[0] << "\n";
  int cur = 0;
  heap[cur] = heap[heap.size() - 1];
  heap.pop_back();

  while (true)
  {
    int left = cur * 2 + 1;
    int right = cur * 2 + 2;
    int largest = cur;

    if (left < heap.size() && heap[left] > heap[largest])
      largest = left;
    if (right < heap.size() && heap[right] > heap[largest])
      largest = right;

    if (largest == cur)
      break;

    swap(heap[cur], heap[largest]);
    cur = largest;
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 0; i < n; ++i)
  {
    int x;
    cin >> x;

    if (x > 0)
      heapInsert(x);
    else if (x == 0)
      heapDelete();
  }
}