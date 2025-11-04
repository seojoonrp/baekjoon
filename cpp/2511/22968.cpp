#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;

vector<ll> max_nodes;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tc;
  cin >> tc;

  max_nodes.push_back(0);
  max_nodes.push_back(1);

  while (tc--) {
    ll n;
    cin >> n;

    int i = 1;
    while (n >= max_nodes[i]) {
      if ((int)max_nodes.size() == i + 1) {
        max_nodes.push_back(max_nodes[i - 1] + max_nodes[i] + 1);
      }

      i++;
    }

    cout << i - 1 << '\n';
  }
}