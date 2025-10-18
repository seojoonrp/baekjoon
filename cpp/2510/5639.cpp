#include <iostream>
#include <vector>
using namespace std;

vector<int> nodes;

void post_search(int lo, int hi) {
  if (lo >= hi) return;

  int bound;
  for (bound = lo + 1; bound < hi; bound++) {
    if (nodes[bound] > nodes[lo]) break;
  }

  post_search(lo + 1, bound);
  post_search(bound, hi);
  cout << nodes[lo] << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int x;
  while (cin >> x) nodes.push_back(x);

  post_search(0, (int)nodes.size());
}