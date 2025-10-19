#include <iostream>
#include <vector>
#include <algorithm>

template <typename Type>
class Tree {
private:
  Type value;
  Tree *parent;
  std::vector<Tree *> children;
  
public:
  Tree(Type const &v = Type(), Tree *p = nullptr) : value(v), parent(p) {}
  
  void set_value(const Type& v) { value = v; }

  Type get_value() const { return value; }

  int get_degree() const { return (int)children.size(); };

  bool is_leaf() const { return children.empty(); }

  void attach_subtree(Tree<Type> *subtree) {
    if (subtree && subtree->parent == nullptr) {
      subtree->parent = this;
      this->children.push_back(subtree);
    }
  }

  void detach_from_parent() {
    if (this->parent != nullptr) {
      auto& parent_children = this->parent->children;

      parent_children.erase(
        std::remove(parent_children.begin(), parent_children.end(), this),
        parent_children.end()
      );

      this->parent = nullptr;
    }
  }

  const std::vector<Tree<Type>*>& get_children() const { return children; }
};

void count_leaves(Tree<int>* node, int& count) {
  if (node->is_leaf()) {
    count++;
    return;
  }

  for (Tree<int>* child : node->get_children()) {
    count_leaves(child, count);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  std::cin >> n;

  std::vector<Tree<int>> nodes(n);
  for (int i = 0; i < n; i++) nodes[i].set_value(i);

  int root_idx = -1;
  for (int i = 0; i < n; i++) {
    int parent_idx;
    std::cin >> parent_idx;

    if (parent_idx == -1) {
      root_idx = i;
    } else {
      nodes[parent_idx].attach_subtree(&nodes[i]);
    }
  }

  int delete_idx;
  std::cin >> delete_idx;

  if (delete_idx == root_idx) {
    std::cout << 0 << '\n';
    return 0;
  }

  nodes[delete_idx].detach_from_parent();

  int leaf_count = 0;
  if (root_idx != -1) {
    count_leaves(&nodes[root_idx], leaf_count);
  }

  std::cout << leaf_count << '\n';
}