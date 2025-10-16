#include <iostream>
#include <vector>
using namespace std;

const int N_MAX = 1001;
const int M_MAX = 1001;

int n, m;
vector<int> jobs[N_MAX];
int person[M_MAX];
bool visited[N_MAX];

bool can_assign(int cur_p) {
  if (visited[cur_p]) return false;

  visited[cur_p] = true;

  for (int job : jobs[cur_p]) {
    if (person[job] == -1 || can_assign(person[job])) {
      person[job] = cur_p;
      return true;
    }
  }

  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    int job_count;
    cin >> job_count;
    jobs[i].resize(job_count);
    for (int j = 0; j < job_count; j++) {
      cin >> jobs[i][j];
    }
  }

  fill(person + 1, person + m + 1, -1);
  int ans = 0;

  for (int i = 1; i <= n; i++) {
    fill(visited + 1, visited + n + 1, false);
    if (can_assign(i)) ans++;
    
    fill(visited + 1, visited + n + 1, false);
    if (can_assign(i)) ans++;
  }

  cout << ans << '\n';
}