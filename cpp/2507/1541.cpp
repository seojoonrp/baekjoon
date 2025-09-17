#include <iostream>
#include <string>
using namespace std;

int num[26];
char oper[26];

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  string s;
  cin >> s;

  int numidx = 0;
  int operidx = 0;
  string temp = "";
  for (int i = 0; i < s.length(); ++i)
  {
    if (s[i] == '+' || s[i] == '-')
    {
      oper[operidx++] = s[i];
      num[numidx++] = stoi(temp);
      temp = "";
    }
    else
      temp += s[i];
  }
  num[numidx++] = stoi(temp);

  bool flag = false;
  for (int i = 0; i < operidx; ++i)
  {
    if (flag)
      oper[i] = '-';
    if (oper[i] == '-' && !flag)
      flag = true;
  }

  int ans = num[0];
  for (int i = 1; i < numidx; ++i)
  {
    if (oper[i - 1] == '+')
      ans += num[i];
    else
      ans -= num[i];
  }

  cout << ans << endl;
}