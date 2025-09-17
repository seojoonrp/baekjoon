#include <iostream>
#include <numeric>
using namespace std;

int main()
{
  int n;
  cin >> n;

  int dp[10] = {0};
  for (int i = 1; i <= 9; ++i)
    dp[i] = 1;

  for (int digit = 2; digit <= n; ++digit)
  {
    int temp[10] = {0};
    for (int i = 0; i < 10; ++i)
    {
      if (i > 0)
        temp[i] = (temp[i] + dp[i - 1]) % 1000000000;
      if (i < 9)
        temp[i] = (temp[i] + dp[i + 1]) % 1000000000;
    }
    for (int i = 0; i < 10; ++i)
      dp[i] = temp[i];
  }

  long long result = 0;
  for (int i = 0; i < 10; ++i)
    result = (result + dp[i]) % 1000000000;

  cout << result << endl;
}
