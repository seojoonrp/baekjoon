#include <iostream>
using namespace std;

int n, r, c;

int calcZ(int size, int x, int y, int start) {
  if (size == 1) {
    if (x == 0 && y == 0) return start + 0;
    if (x == 0 && y == 1) return start + 1;
    if (x == 1 && y == 0) return start + 2;
    if (x == 1 && y == 1) return start + 3;
  }

  int partLen = 1 << (size - 1);
  int partArea = 1 << (2 * size - 2);

  if (x < partLen && y < partLen) return start + calcZ(size - 1, x, y, 0);
  if (x < partLen && y >= partLen) return start + calcZ(size - 1, x, y - partLen, partArea);
  if (x >= partLen && y < partLen) return start + calcZ(size - 1, x - partLen, y, partArea * 2);
  if (x >= partLen && y >= partLen) return start + calcZ(size - 1, x - partLen, y - partLen, partArea * 3);

  return -1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> r >> c;

  cout << calcZ(n, r, c, 0) << '\n';
}