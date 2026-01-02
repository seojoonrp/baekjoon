#include <iostream>
#include <string>
#include <set>
using namespace std;

struct Rule {
  int write;
  char next_state;
  int dir;
};

int n, l;
Rule rules[17][2];
string tape;
set<pair<string, pair<int, char>>> visited;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  char init_state;
  cin >> init_state;
  cin >> n >> l;

  for (int i = 0; i < 16; i++) {
    rules[i][0].write = -1;
    rules[i][1].write = -1;
  }

  for (int i = 0; i < n; i++) {
    char state; int read;
    cin >> state >> read;
    Rule& r = rules[state - 'A'][read];
    cin >> r.write >> r.next_state >> r.dir;
  }

  cin >> tape;
  
  int idx = 0;
  char state = init_state;
  bool cycle = false;

  while (true) {
    if (visited.count({ tape, { idx, state }})) {
      cycle = true;
      break;
    }

    visited.insert({ tape, { idx, state }});

    Rule& cur_rule = rules[state - 'A'][tape[idx] - '0'];
    if (cur_rule.write == -1) break;

    int next_idx = idx + cur_rule.dir;
    if (next_idx < 0 || next_idx >= l) break;

    tape[idx] = '0' + cur_rule.write;
    state = cur_rule.next_state;
    idx = next_idx;
  }

  if (cycle) cout << "CONTINUE" << '\n';
  else cout << "STOP" << '\n';;
}