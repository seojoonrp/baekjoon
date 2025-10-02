#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int MAX = 10;

int char_to_idx(const char& c) { return c - '0'; }

struct Trie {
  bool is_terminal;
  Trie* children[MAX];

  Trie(): is_terminal(false) {
    fill(children, children + MAX, nullptr);
  }

  ~Trie() {
    for (int i = 0; i < MAX; i++) {
      if (children[i]) delete children[i];
    }
  }

  void insert(string word) {
    Trie* cur = this;

    for (char c : word) {
      int index = char_to_idx(c);
      if (cur->children[index] == nullptr) {
        cur->children[index] = new Trie();
      }

      cur = cur->children[index];
    }

    cur->is_terminal = true;
  }

  bool find(string word) {
    Trie* cur = this;

    for (char c : word) {
      int index = char_to_idx(c);
      if (cur->children[index] == nullptr) return false;

      cur = cur->children[index];
    }

    if (cur->is_terminal) return true;
  }

  bool consistent() {
    if (is_terminal) {
      for (int i = 0; i < MAX; i++) {
        if (children[i] != nullptr) return false;
      }
    }

    for (int i = 0; i < MAX; i++) {
      if (children[i] && !children[i]->consistent()) return false;
    }

    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tc;
  cin >> tc;

  while (tc--) {
    int n;
    cin >> n;

    Trie* root = new Trie();

    for (int i = 0; i < n; i++) {
      string s;
      cin >> s;
      root->insert(s);
    }

    cout << (root->consistent() ? "YES" : "NO") << '\n';

    delete root;
  }
}