#include <iostream>
#include <vector>
using namespace std;

vector<pair<int, int>> ans;

void hanoi(int n, int from, int to, int via) {
  if (n == 1) {
    ans.push_back(make_pair(from, to));
    return;
  }

  hanoi(n - 1, from, via, to);
  hanoi(1, from, to, via);
  hanoi(n - 1, via, to, from);
}

int main() {
  int n;
  cin >> n;

  hanoi(n, 1, 3, 2);

  cout << ans.size() << "\n";
  for (auto& mov : ans) {
    cout << mov.first << " " << mov.second << " " << "\n";
  }
}