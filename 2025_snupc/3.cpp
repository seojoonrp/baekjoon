#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tc;
  cin >> tc;

  while (tc--) {
    int n;
    cin >> n;

    int sqn = (int)sqrt(n);

    // if (sqn >= (n + 1) / 2) {
    //   cout << "YES\n";
    if (n == 1) {
      cout << "YES\n";
      cout << 1 << '\n';
      cout << 1 << '\n';
    } else if (n == 2) {
      cout << "YES\n";
      cout <<"1 2" << '\n';
      cout << "1 2" << '\n';
    } else if (n == 4) {
      cout << "YES\n";
      cout <<"1 2 3 4" << '\n';
      cout << "1 2 4 3" << '\n';
    } else {
      cout << "NO\n";
    }
  }
}