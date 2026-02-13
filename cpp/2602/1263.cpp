#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 1e3 + 5;

struct Job {
  int t;
  int due;
};

int n;
Job jobs[MAX];

bool job_cmp(Job& j1, Job& j2) {
  if (j1.due == j2.due) return j1.t < j2.t;
  return j1.due < j2.due;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> jobs[i].t >> jobs[i].due;
  }

  sort(jobs, jobs + n, job_cmp);

  int over = jobs[0].t;
  int cur = jobs[0].due;
  for (int i = 1; i < n; i++) {
    Job job = jobs[i];
    if (cur + job.t >= job.due) {
      over += (cur + job.t - job.due);
      cur = job.due;
    } else {
      cur += job.t;
    }
  }

  int ans = jobs[0].due - over;
  if (ans < 0) cout << -1 << '\n';
  else cout << ans << '\n';
}