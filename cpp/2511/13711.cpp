#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX = 100001;

int n;
int arr[MAX], index[MAX];

int lis() {
  vector<int> pseudo_lis;

  for (int i = 1; i <= n; i++) {
    auto it = upper_bound(pseudo_lis.begin(), pseudo_lis.end(), arr[i]);

    if (it == pseudo_lis.end()) {
      pseudo_lis.push_back(arr[i]);
    } else {
      *it = arr[i];
    }
  }

  return pseudo_lis.size();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;

  for (int i = 1; i <= n; i++) {
    int num;
    cin >> num;
    index[num] = i;
  }

  for (int i = 1; i <= n; i++) {
    int num;
    cin >> num;
    arr[i] = index[num];
  }

  cout << lis() << '\n';
}