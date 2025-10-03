#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

const int ALPHABET = 26;
const int MAX_NODES = 5e6;

struct TrieNode {
  bool is_terminal;
  TrieNode* children[ALPHABET];

  void clear() {
    is_terminal = false;
    fill(children, children + ALPHABET, nullptr);
  }
};

vector<TrieNode> node_pool;
int node_idx;

TrieNode* newNode() {
  node_pool[node_idx].clear();
  return &node_pool[node_idx++];
}

struct Trie {
  TrieNode* root;

  Trie() {
    root = newNode();
  }

  void insert(string word) {
    TrieNode* cur = root;

    for (char c : word) {
      int index = c - 'a';
      if (cur->children[index] == nullptr) cur->children[index] = newNode();
      cur = cur->children[index];
    }

    cur->is_terminal = true;
  }

  vector<int> terminal_idx(string word) {
    TrieNode* cur = root;
    vector<int> ret;

    for (int i = 0; i < word.length(); i++) {
      int index = word[i] - 'a';
      if (cur->children[index] == nullptr) break;
      cur = cur->children[index];

      if (cur->is_terminal) ret.push_back(i);
    }

    return ret;
  }

  bool legend(string word, int start) {
    TrieNode* cur = root;

    for (int i = start; i < word.length(); i++) {
      int index = word[i] - 'a';
      if (cur->children[index] == nullptr) return false;
      cur = cur->children[index];
    }

    return cur->is_terminal;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int c, n;
  cin >> c >> n;
  
  node_pool.resize(MAX_NODES);

  node_idx = 0;
  Trie color_trie, nickname_trie;

  for (int i = 0; i < c; i++) {
    string s;
    cin >> s;
    color_trie.insert(s);
  }
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    nickname_trie.insert(s);
  }

  int q;
  cin >> q;
  for (int i = 0; i < q; i++) {
    bool ans = false;
    string s;
    cin >> s;

    vector<int> term = color_trie.terminal_idx(s);
    for (int idx : term) {
      if (idx != s.length() - 1 && nickname_trie.legend(s, idx + 1)) {
        ans = true;
        break;
      }
    }

    cout << (ans ? "Yes" : "No") << '\n';
  }
}