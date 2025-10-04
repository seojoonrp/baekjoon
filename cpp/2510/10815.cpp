#include <iostream>
#include <set>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  set<int> st;
  
  cin >> n;
  while (n--) {
    int x;
    cin >> x;
    st.insert(x);
  }

  cin >> m;
  while (m--) {
    int x;
    cin >> x;

    set<int>::iterator iter;
    iter = st.find(x);

    if (iter != st.end()) cout << "1 ";
    else cout << "0 ";
  }

  cout << '\n';
}