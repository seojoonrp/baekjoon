#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int MAX = 26;

struct TrieNode {
  bool is_terminal;
  TrieNode* children[MAX];
  int child_num;

  TrieNode() : is_terminal(false), child_num(0) {
    fill(children, children + MAX, nullptr);
  }

  ~TrieNode() {
    for (int i = 0; i < MAX; i++) {
      if (children[i]) delete children[i];
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

  void insert(const string& word) {
    TrieNode* cur = this->root;

    for (const char& c : word) {
      int index = c - 'a';
      if (cur->children[index] == nullptr) {
        cur->children[index] = new TrieNode();
        cur->child_num++;
      }
      cur = cur->children[index];
    }

    cur->is_terminal = true;
  }

  int search(const string& word) {
    TrieNode* cur = this->root;
    int cnt = 0;

    for (const char& c : word) {
      int index = c - 'a';
      TrieNode* next = cur->children[index];

      if (next == nullptr) {
        cout << "something is wrong.\n";
        return -1;
      }

      if (cur->child_num != 1 || cur->is_terminal || cur == this->root) cnt++;
      cur = next;
    }

    return cnt;
  }
};

string words[100001];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cout << fixed;
  cout.precision(2);

  int n;
  while (cin >> n) {
    Trie* trie = new Trie();
    double ans = 0;

    for (int i = 0; i < n; i++) {
      cin >> words[i];
      trie->insert(words[i]);
    }

    for (int i = 0; i < n; i++) {
      int cnt = (trie->search(words[i]));
      ans += static_cast<double>(cnt);
    }

    cout << (ans / n) << '\n';

    delete trie;
  }
}