#include <iostream>
#include <deque>
using namespace std;

int n;
deque<int> dq;

int main() {
  cin >> n;

  for (int i = 1; i <= n; ++i) dq.push_back(i);

  while (dq.size() > 1) {
    dq.pop_front();
    int cur = dq.front();
    dq.pop_front();
    dq.push_back(cur);
  }

  cout << dq.front() << '\n';
}