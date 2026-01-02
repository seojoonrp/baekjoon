// 기본적인 그리디 -> 첫 인덱스부터 3개씩 묶고, 안되면 2개, 안되면 1개씩 묶어서 없애기
// 문제점 -> 1 2 1 1일 때. 처음 두 개 묶고 뒤에서 세 개 묶는 게 더 싸다.
// 언제 발생? -> A[i+1] > A[i+2]일 때. 두 개 묶는 게 이득이다. 5+5=7+3이므로

#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 1e4 + 5;

int n;
int arr[MAX];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> arr[i];

  int ans = 0;

  for (int i = 1; i <= n; i++) {
    if (arr[i + 1] > arr[i + 2]) {
      int two_sel = min(arr[i], arr[i + 1] - arr[i + 2]);
      arr[i] -= two_sel;
      arr[i + 1] -= two_sel;
      ans += two_sel * 5;
    }

    int three_sel = min({ arr[i], arr[i + 1], arr[i + 2] });
    arr[i] -= three_sel;
    arr[i + 1] -= three_sel;
    arr[i + 2] -= three_sel;
    ans += three_sel * 7;

    ans += arr[i] * 3;
    arr[i] = 0;
  }

  cout << ans << '\n';
}