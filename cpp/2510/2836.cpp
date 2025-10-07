#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;

struct Move {
  ll start;
  ll end;
};

bool compare_move(const Move& m1, const Move& m2) {
  if (m1.start == m2.start) return m1.end > m2.end;
  return m1.start < m2.start;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  ll m;
  cin >> n >> m;

  int backward = 0;
  vector<Move> moves;

  while (n--) {
    ll a, b;
    cin >> a >> b;
    if (a > b) {
      moves.push_back({ b, a }); // 편의상 반대로
      backward++;
    }
  }

  ll ans = 0;
  if (!moves.empty()) {
    sort(moves.begin(), moves.end(), compare_move);

    ll lo = moves[0].start;
    ll hi = moves[0].end;

    for (int i = 1; i < backward; i++) {
      Move& move = moves[i];

      if (move.end <= hi) continue;

      if (move.start <= hi) hi = move.end;
      else {
        ans += hi - lo;
        lo = move.start;
        hi = move.end;
      }
    }
    ans += hi - lo;
  }
  
  cout << m + ans * 2 << '\n';
}