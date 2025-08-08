#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000;

vector<vector<int>> mult(const vector<vector<int>> &a, const vector<vector<int>> &b, int n)
{
  vector<vector<int>> res(n, vector<int>(n, 0));

  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      for (int k = 0; k < n; ++k)
      {
        res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % MOD;
      }
    }
  }

  return res;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n;
  long long e;
  cin >> n >> e;

  vector<vector<int>> a(n, vector<int>(n));
  vector<vector<int>> ans(n, vector<int>(n, 0));

  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      cin >> a[i][j];
      a[i][j] %= MOD;
      if (i == j)
        ans[i][j] = 1;
    }
  }

  while (e > 0)
  {
    if (e % 2 == 1)
    {
      ans = mult(ans, a, n);
    }
    a = mult(a, a, n);
    e /= 2;
  }

  for (const auto &row : ans)
  {
    for (const auto &val : row)
    {
      cout << val << " ";
    }
    cout << "\n";
  }

  return 0;
}
