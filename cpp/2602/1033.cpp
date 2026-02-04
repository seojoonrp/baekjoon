#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

const int MAX = 11;

// to = from * (bunja / bunmo)
struct Edge {
  int to;
  ll bunja;
  ll bunmo;
};

int n;
vector<Edge> tree[MAX];
vector<ll> bunja, bunmo;

void dfs(int cur, int parent) {
  for (Edge& e : tree[cur]) {
    if (e.to == parent) continue;

    bunja[e.to] = bunja[cur] * e.bunja;
    bunmo[e.to] = bunmo[cur] * e.bunmo;
    dfs(e.to, cur);
  }
}

ll gcd(ll a, ll b) {
  if (a < b) swap(a, b);
  
  if (a % b == 0) return b;
  return gcd(b, a % b);
}

ll lcm(ll a, ll b) {
  return a * b / gcd(a, b);
}

ll gcd_many(vector<ll>& vec) {
  ll ans = gcd(vec[0], vec[1]);
  for (int i = 2; i < (int)vec.size(); i++) {
    ans = gcd(ans, vec[i]);
  }
  return ans;
}

ll lcm_many(vector<ll>& vec) {
  ll ans = 1;
  for (ll x : vec) ans = lcm(ans, x);
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i < n; i++) {
    int a, b;
    ll bj, bm;
    cin >> a >> b >> bj >> bm;
    tree[b].push_back({a, bj, bm});
    tree[a].push_back({b, bm, bj});
  }

  if (n == 1) {
    cout << 1 << '\n';
    return 0;
  }

  bunja.resize(n);
  bunmo.resize(n);

  bunja[0] = bunmo[0] = 1;
  dfs(0, -1);

  ll LCM = lcm_many(bunmo);
  for (int i = 0; i < n; i++) {
    bunja[i] *= LCM / bunmo[i];
  }
  ll GCD = gcd_many(bunja);
  for (int i = 0; i < n; i++) {
    bunja[i] /= GCD;
    cout << bunja[i] << ' ';
  }
  cout << '\n';
}
