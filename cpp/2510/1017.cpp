#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

int n;
bool is_prime[2001];
vector<int> sources, sinks;
vector<int> graph[51];
bool visited[51];
int source[51];

void fill_is_prime(int max_n) {
  fill(is_prime, is_prime + max_n + 1, true);

  for (int i = 2; i <= sqrt(max_n); i++) {
    if (is_prime[i]) {
      for (int j = i * i; j <= max_n; j += i) is_prime[j] = false;
    }
  }
}

bool can_assign(int cur) {
  if (visited[cur]) return false;

  visited[cur] = true;

  for (int si : graph[cur]) {
    if (source[si] == -1 || can_assign(source[si])) {
      source[si] = cur;
      return true;
    }
  }

  return false;
}

bool can_match() {
  fill(source, source + n / 2, -1);
  int matched = 0;

  for (int i = 0; i < n / 2; i++) {
    fill(visited, visited + n / 2, false);

    if (can_assign(i)) matched++;
  }

  return matched == (n / 2);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;

  int nums[51];
  for (int i = 0; i < n; i++) cin >> nums[i];
  for (int i = 0; i < n; i++) {
    if ((nums[i] - nums[0]) % 2 == 0) sources.push_back(nums[i]);
    else sinks.push_back(nums[i]);
  }

  if (sources.size() != sinks.size()) {
    cout << "-1\n";
    return 0;
  }

  fill_is_prime(2000);

  for (int i = 0; i < n / 2; i++) {
    for (int j = 0; j < n / 2; j++) {
      if (is_prime[sources[i] + sinks[j]]) graph[i].push_back(j);
    }
  }

  vector<int> first_conn = graph[0];
  vector<int> ans;

  for (int si : first_conn) {
    graph[0].clear();
    graph[0].push_back(si);

    if (can_match()) ans.push_back(sinks[si]);
  }

  if (ans.empty()) cout << "-1\n";
  else {
    sort(ans.begin(), ans.end());
    for (int x : ans) cout << x << ' ';
    cout << '\n';
  }
}