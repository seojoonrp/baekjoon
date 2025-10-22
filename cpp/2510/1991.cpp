#include <iostream>
using namespace std;

struct TreeNode {
  char value;
  TreeNode* left;
  TreeNode* right;

  TreeNode() {
    value = ' ';
    left = nullptr;
    right = nullptr;
  }

  TreeNode(char value) : value(value) {
    left = nullptr;
    right = nullptr;
  }
};

void preorder(TreeNode* cur) {
  if (cur == nullptr) return;

  cout << cur->value;
  preorder(cur->left);
  preorder(cur->right);
}

void inorder(TreeNode* cur) {
  if (cur == nullptr) return;

  inorder(cur->left);
  cout << cur->value;
  inorder(cur->right);
}

void postorder(TreeNode* cur) {
  if (cur == nullptr) return;

  postorder(cur->left);
  postorder(cur->right);
  cout << cur->value;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;

  TreeNode* nodes[26];
  for (int i = 0; i < 26; i++) nodes[i] = nullptr;

  for (int i = 0; i < n; i++) {
    char par_val, l_val, r_val;
    cin >> par_val >> l_val >> r_val;

    int par_idx = par_val - 'A';

    if (nodes[par_idx] == nullptr) {
      nodes[par_idx] = new TreeNode(par_val);
    }
    
    if (l_val != '.') {
      int l_idx = l_val - 'A';
      if (nodes[l_idx] == nullptr) {
        nodes[l_idx] = new TreeNode(l_val);
      }
      nodes[par_idx]->left = nodes[l_idx];
    }
    if (r_val != '.') {
      int r_idx = r_val - 'A';
      if (nodes[r_idx] == nullptr) {
        nodes[r_idx] = new TreeNode(r_val);
      }
      nodes[par_idx]->right = nodes[r_idx];
    }
  }

  preorder(nodes[0]);
  cout << '\n';
  inorder(nodes[0]);
  cout << '\n';
  postorder(nodes[0]);
  cout << '\n';

  for (int i = 0; i < 26; i++) {
    delete nodes[i];
  }
}