#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n;
priority_queue<int> max_pq;
priority_queue<int, vector<int>, greater<>> min_pq;

void swap_pq_top() {
  if (max_pq.empty() || min_pq.empty()) return;
  
  int max_top = max_pq.top();
  int min_top = min_pq.top();

  if (max_top > min_top) {
    max_pq.pop();
    max_pq.push(min_top);
    min_pq.pop();
    min_pq.push(max_top);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;

    if (i % 2 == 0) {
      min_pq.push(x);
    } else {
      max_pq.push(x);
    }
    
    swap_pq_top();
    cout << max_pq.top() << '\n';
  }
}