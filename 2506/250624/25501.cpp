#include <iostream>
#include <string>
using namespace std;

// Call by Reference가 훨씬 더 빠르다. 어지간하면 이걸로 쓰기
int recursion(const string& s, int l, int r, int& recCount) {
  recCount++;

  if (l >= r) return 1;
  else if (s[l] != s[r]) return 0;
  else return recursion(s, l + 1, r - 1, recCount);
}

int isPalindrome(const string& s, int& recCount) {
  return recursion(s, 0, s.length() - 1, recCount);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;

  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;

    int recursionCallCount = 0;
    cout << isPalindrome(s, recursionCallCount) << " " << recursionCallCount << "\n";
  }
}