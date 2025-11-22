#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

struct Gem {
  int weight;
  ll value;
};

bool cmp_by_weight(const Gem& g1, const Gem& g2) {
  return g1.weight < g2.weight;
}

struct gem_priority {
  bool operator()(const Gem& g1, const Gem& g2) {
    return g1.value < g2.value;
  }
};

int n, k;
vector<Gem> gems;
vector<int> backpacks;
priority_queue<Gem, vector<Gem>, gem_priority> pq;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> k;

  gems.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> gems[i].weight >> gems[i].value;
  }

  backpacks.resize(k);
  for (int i = 0; i < k; i++) {
    cin >> backpacks[i];
  }

  sort(gems.begin(), gems.end(), cmp_by_weight);
  sort(backpacks.begin(), backpacks.end());

  ll total_value = 0;

  int gem_idx = 0;
  for (int i = 0; i < k; i++) {
    while (gems[gem_idx].weight <= backpacks[i] && gem_idx < n) {
      pq.push(gems[gem_idx]);
      gem_idx++;
    }

    if (!pq.empty()) {
      Gem top_gem = pq.top();
      total_value += top_gem.value;
      pq.pop();
    }
  }

  cout << total_value << '\n';
}