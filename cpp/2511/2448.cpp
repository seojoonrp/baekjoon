#include <iostream>
#include <string>
using namespace std;

const int MAX = 3100;

int n;
bool cur_arr[MAX], prev_arr[MAX];

void pattern(int p) {
  if (p == 1) cout << "  *  ";
  if (p == 2) cout << " * * ";
  if (p == 3) cout << "*****";

  if (p == 0) cout << "     ";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;

  cur_arr[1] = true;

  for (int row = 1; row <= n / 3; row++) {
    for (int pat = 1; pat <= 3; pat++) {
      for (int i = 1; i <= (n / 3) - row; i++) cout << "   ";
      
      for (int i = 1; i <= row; i++) {
        if (cur_arr[i]) pattern(pat);
        else pattern(0);

        if (i != row) cout << ' ';
      }

      for (int i = 1; i <= (n / 3) - row; i++) cout << "   ";

      cout << '\n';
    }

    for (int i = 1; i <= row; i++) {
      prev_arr[i] = cur_arr[i];
    }

    cur_arr[1] = true;
    cur_arr[row + 1] = true;
    for (int i = 2; i <= row; i++) {
      if (prev_arr[i - 1] != prev_arr[i]) {
        cur_arr[i] = true;
      } else cur_arr[i] = false;
    }
  }
}