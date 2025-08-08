#include <iostream>
#include <climits>
using namespace std;

int n;
int* num;
int* oper;
int ansMax = INT_MIN;
int ansMin = INT_MAX;

void calc(int idx, int cur) {
  if (idx == n) {
    if (cur > ansMax) ansMax = cur;
    if (cur < ansMin) ansMin = cur;
    return;
  }

  int next = num[idx];
  if (oper[0] > 0) {
    oper[0]--;
    calc(idx + 1, cur + next);
    oper[0]++;
  }
  if (oper[1] > 0) {
    oper[1]--;
    calc(idx + 1, cur - next);
    oper[1]++;
  }
  if (oper[2] > 0) {
    oper[2]--;
    calc(idx + 1, cur * next);
    oper[2]++;
  }
  if (oper[3] > 0) {
    oper[3]--;
    if (cur < 0) calc(idx + 1, -(-cur / next));
    else calc(idx + 1, cur / next);
    oper[3]++;
  }
}

int main() {
  ios::sync_with_stdio(false);

  cin >> n;
  num = new int[n];
  for (int i = 0; i < n; ++i) cin >> num[i];
  oper = new int[4];
  for (int i = 0; i < 4; ++i) cin >> oper[i];

  calc(1, num[0]);

  cout << ansMax << endl << ansMin << endl;

  delete[] num;
  delete[] oper;
}