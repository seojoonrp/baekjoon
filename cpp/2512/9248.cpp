#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using pii = pair<int, int>;

const int MAX = 5e5 + 5;

string s;
int n;
int r[MAX], sa[MAX], lcp[MAX];
pii rp[MAX];
vector<pii> sort_rp;

bool compare_pii(const pii& a, const pii& b) {
  if (a.first == b.first) return a.second < b.second;
  return a.first < b.first;
}

void get_rank() {
  for (int i = 0; i < n; i++) {
    r[i] = lower_bound(sort_rp.begin(), sort_rp.end(), rp[i]) - sort_rp.begin();
  }
  sort_rp.resize(n);
}

void get_rank_pair(int step) {
  for (int i = 0; i < n; i++) {
    rp[i].first = r[i];
    if (i + step >= n) rp[i].second = -1;
    else rp[i].second = r[i + step];

    sort_rp[i] = rp[i];
  }

  sort(sort_rp.begin(), sort_rp.end(), compare_pii);
  sort_rp.erase(unique(sort_rp.begin(), sort_rp.end()), sort_rp.end());
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> s;
  n = s.length();
  sort_rp.resize(n);

  vector<char> sort_s;
  for (int i = 0; i < n; i++) sort_s.push_back(s[i]);
  sort(sort_s.begin(), sort_s.end());
  sort_s.erase(unique(sort_s.begin(), sort_s.end()), sort_s.end());

  for (int i = 0; i < n; i++) {
    r[i] = lower_bound(sort_s.begin(), sort_s.end(), s[i]) - sort_s.begin();
  }

  int step = 1;
  while (step < n) {
    get_rank_pair(step);
    get_rank();
    step *= 2;
  }

  for (int i = 0; i < n; i++) sa[r[i]] = i;
  for (int i = 0; i < n; i++) cout << sa[i] + 1 << ' ';
  cout << '\n';

  int h = 0;
  for (int i = 0; i < n; i++) {
    if (r[i] == 0) continue;
    
    int j = sa[r[i] - 1];
    
    if (h > 0) h--;
    
    while (i + h < n && j + h < n && s[i + h] == s[j + h]) {
      h++;
    }
    
    lcp[r[i]] = h;
  }

  cout << 'x' << ' ';
  for (int i = 1; i < n; i++) cout << lcp[i] << ' ';
  cout << '\n';
}