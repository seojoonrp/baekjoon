#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 30;

struct TrieNode {
  TrieNode* children[2];

  TrieNode() {
    fill(children, children + 2, nullptr);
  }

  ~TrieNode() {
    delete children[0];
    delete children[1];
  }
};

struct Trie {
  TrieNode* root;

  Trie() {
    root = new TrieNode();
  }

  ~Trie() {
    delete root;
  }

  int insert(int num) {
    int cur_ans = 0;
    TrieNode* cur = this->root;
    TrieNode* max_node = this->root;

    for (int i = MAX; i >=0; i--) {
      int index;
      if (num & (1 << i)) index = 1;
      else index = 0;

      if (cur->children[index] == nullptr) {
        cur->children[index] = new TrieNode();
      }

      bool success;
      if (max_node->children[1 - index] != nullptr) {
        success = true;
        max_node = max_node->children[1 - index];
      } else {
        success = false;
        max_node = max_node->children[index];
      }
      
      if (success) cur_ans = cur_ans * 2 + 1;
      else cur_ans = cur_ans * 2;

      cur = cur->children[index];
    }

    return cur_ans;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  int ans = 0;
  Trie* trie = new Trie();

  cin >> n;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    ans = max(ans, trie->insert(x));
  }

  cout << ans << '\n';

  delete trie;
}