#include <iostream>
#include <vector>
using namespace std;

const int MAX = 51;
const int KNOW = 0;

int n, m;
int parent[MAX], s[MAX];
vector<int> party_people[MAX];

int find_root(int i) {
  if (parent[i] == i) return i;
  else return parent[i] = find_root(parent[i]);
}

void union_root(int r1, int r2) {
  int new_size = s[r1] + s[r2];

  if (s[r1] > s[r2]) {
    parent[r2] = r1;
    s[r1] = new_size;
  } else {
    parent[r1] = r2;
    s[r2] = new_size;
  }
}

void union_node(int x, int y) {
  int rx = find_root(x);
  int ry = find_root(y);
  
  if (x != y) union_root(rx, ry);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  for (int i = 0; i <= n; i++) {
    parent[i] = i;
  }

  int know_cnt;
  cin >> know_cnt;
  for (int i = 1; i <= know_cnt; i++) {
    int per;
    cin >> per;
    union_node(KNOW, per);
  }

  for (int i = 1; i <= m; i++) {
    int party_size, leader;
    cin >> party_size;
      
    cin >> leader;
    party_people[i].push_back(leader);

    for (int j = 2; j <= party_size; j++) {
      int per;
      cin >> per;
      party_people[i].push_back(per);
      union_node(leader, per);
    }
  }

  int know_root = find_root(KNOW);
  int ans = 0;

  for (int i = 1; i <= m; i++) {
    bool truth = false;

    for (int& per : party_people[i]) {
      if (find_root(per) == know_root) truth = true;
    }

    if (!truth) ans++;
  }

  cout << ans << '\n';
}