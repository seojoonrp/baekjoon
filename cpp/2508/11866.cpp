#include <iostream>
#include <vector>
using namespace std;

int n, k;
vector<int> vec;

int main() {
  cin >> n >> k;
  k--;

  for (int i = 1; i <= n; ++i) vec.push_back(i);

  int cur = k;
  cout << '<';
  while (true) {
    if (vec.size() == 1) {
      cout << vec[cur] << ">\n";
      break;
    }
    cout << vec[cur] << ", ";
    vec.erase(vec.begin() + cur);
    cur += k;
    if (cur >= vec.size()) cur %= vec.size();
  }
}