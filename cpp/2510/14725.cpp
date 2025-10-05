#include <iostream>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

struct TrieNode {
  map<string, TrieNode*> children;

  ~TrieNode() {
    for (auto& child : children) {
      delete child.second;
    }
  }

  void Search(int cur_depth) {
    for (auto& child : children) {
      for (int i = 0; i < cur_depth; i++) cout << "--";
      cout << child.first << '\n';

      child.second->Search(cur_depth + 1);
    }
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

  void Insert(vector<string>& foods) {
    TrieNode* cur = root;

    for (string& food : foods) {
      if (cur->children.find(food) == cur->children.end()) {
        TrieNode* new_node = new TrieNode();
        cur->children.insert({ food, new_node });
      }

      cur = cur->children[food];
    }
  }

  void Search() {
    root->Search(0);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  Trie* trie = new Trie();

  int n;
  cin >> n;
  
  while (n--) {
    int k;
    cin >> k;

    vector<string> foods(k);
    for (int i = 0; i < k; i++) cin >> foods[i];

    trie->Insert(foods);
  }

  trie->Search();
}