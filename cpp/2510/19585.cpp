#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

const int ALPHABET = 26;

struct TrieNode {
  bool is_terminal;
  vector<pair<char, TrieNode*>> children;

  TrieNode(): is_terminal(false) {
    children.clear();
  }
};

struct Trie {
  TrieNode* root;

  Trie() {
    root = new TrieNode();
  }

  void insert(string word) {
    TrieNode* cur = root;

    for (char c : word) {
      bool flag = false;

      for (auto& child : cur->children) {
        if (child.first == c) {
          flag = true;
          cur = child.second;
          break;
        }
      }

      if (!flag) {
        TrieNode* new_node = new TrieNode();
        cur->children.push_back({ c, new_node });
        cur = new_node;
      }
    }

    cur->is_terminal = true;
  }

  void terminal_idx(string& word, bool*& arr) {
    TrieNode* cur = root;

    for (int i = 0; i < word.length(); i++) {
      bool flag = false;

      for (auto& child : cur->children) {
        if (child.first == word[i]) {
          flag = true;
          cur = child.second;
          break;
        }
      }

      if (!flag) break;

      if (cur->is_terminal) arr[i] = true;
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int c, n;
  cin >> c >> n;

  Trie* color_trie = new Trie();
  Trie* nickname_trie = new Trie();

  for (int i = 0; i < c; i++) {
    string s;
    cin >> s;
    color_trie->insert(s);
  }
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    reverse(s.begin(), s.end());
    nickname_trie->insert(s);
  }

  int q;
  cin >> q;
  for (int i = 0; i < q; i++) {
    string s;
    cin >> s;
    string s_rev = s;
    reverse(s_rev.begin(), s_rev.end());

    int l = s.length();
    bool* color_arr = new bool[l];
    bool* nickname_arr = new bool[l];
    fill(color_arr, color_arr + l, false);
    fill(nickname_arr, nickname_arr + l, false);

    color_trie->terminal_idx(s, color_arr);
    nickname_trie->terminal_idx(s_rev, nickname_arr);

    bool found = false;
    for (int i = 0; i < l - 1; i++) {
      if (color_arr[i] && nickname_arr[l - 2 - i]) {
        found = true;
        cout << "Yes" << '\n';
        break;
      }
    }
    if (!found) cout << "No" << '\n';

    delete[] color_arr;
    delete[] nickname_arr;
  }
}