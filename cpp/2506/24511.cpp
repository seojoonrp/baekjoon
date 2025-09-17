#include <iostream>
#include <stack>
#include <deque>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;

  vector<int> A(n);
  for (int i = 0; i < n; ++i) {
    cin >> A[i];
  }
  
  deque<int> q;
  for (int i = 0; i < n; ++i) {
    int num;
    cin >> num;

    if (!A[i]) q.push_front(num);
  }

  int m;
  cin >> m;

  for (int i = 0; i < m; ++i) {
    int num;
    cin >> num;

    q.push_back(num);
    cout << q.front() << " ";
    q.pop_front();
  }
}