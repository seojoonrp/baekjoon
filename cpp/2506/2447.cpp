#include <iostream>
using namespace std;

// char**&나 char**나 여기서는 똑같다. 포인터가 가리키는 내용만 바뀌고, 포인터 자체를 바꿀 일은 없기 때문!
// 성능 차이도 없다.
void star(char** a, int sx, int sy, int n) {
  if (n == 1) return;

  int seg = n / 3;

  for (int i = sx + seg; i < sx + seg * 2; ++i) {
    for (int j = sy + seg; j < sy + seg * 2; ++j) {
      a[i][j] = ' ';
    }
  }

  star(a, sx, sy, seg);
  star(a, sx, sy + seg, seg);
  star(a, sx, sy + seg * 2, seg);
  star(a, sx + seg, sy, seg);
  star(a, sx + seg, sy + seg * 2, seg);
  star(a, sx + seg * 2, sy, seg);
  star(a, sx + seg * 2, sy + seg, seg);
  star(a, sx + seg * 2, sy + seg * 2, seg);
}

int main() {
  int n;
  cin >> n;

  char** a = new char*[n];
  for (int i = 0; i < n; ++i) {
    a[i] = new char[n];
    for (int j = 0; j < n; ++j) a[i][j] = '*';
  }

  star(a, 0, 0, n);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) cout << a[i][j];
    cout << "\n";

    delete[] a[i];
  }
  delete[] a;
}