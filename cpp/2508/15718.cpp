#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// n을 base진법으로 바꾸기
vector<int> convert(int n, int base) {
  vector<int> ans;

  while (n > 0) {
    ans.push_back(n % base);
    n /= base;
  }
  reverse(ans.begin(), ans.end());

  return ans;
}



int lucas(int n, int r, int mod) {

}