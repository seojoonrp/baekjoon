#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <limits>
using namespace std;

const int MAX = 8000;
const int INF = 1e9;

struct Edge {
  int to;
  int capacity;
  int rev;
};

int n, nodes;
unordered_map<string, int> word_node;
unordered_set<string> eng_words, fre_words;
vector<Edge> graph[MAX];
int level[MAX], iter[MAX];

bool is_new(const string& word) {
  return word_node.find(word) == word_node.end();
}

void add_edge(int from, int to, int capacity) {
  graph[from].push_back({ to, capacity, (int)graph[to].size() });
  graph[to].push_back({ from, 0, (int)graph[from].size() - 1 });
}

bool find_level(int source, int sink) {
  fill(level, level + nodes, -1);

  queue<int> q;
  level[source] = 0;
  q.push(source);

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (Edge& edge : graph[cur]) {
      if (edge.capacity > 0 && level[edge.to] == -1) {
        level[edge.to] = level[cur] + 1;
        q.push(edge.to);
      }
    }
  }

  return level[sink] != -1;
}

int blocking_flow(int cur, int sink, int cur_bf) {
  if (cur == sink) return cur_bf;

  for (int& i = iter[cur]; i < (int)graph[cur].size(); i++) {
    Edge& edge = graph[cur][i];

    if (edge.capacity > 0 && level[edge.to] == level[cur] + 1) {
      int next_bf = blocking_flow(edge.to, sink, min(cur_bf, edge.capacity));

      if (next_bf > 0) {
        edge.capacity -= next_bf;
        graph[edge.to][edge.rev].capacity += next_bf;
        return next_bf;
      }
    }
  }

  return 0;
}

int max_flow(int source, int sink) {
  int total_flow = 0;

  while (find_level(source, sink)) {
    fill(iter, iter + nodes, 0);

    int bf;
    while ((bf = blocking_flow(source, sink, INF)) > 0) {
      total_flow += bf;
    }
  }

  return total_flow;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tc;
  cin >> tc;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  for (int tci = 1; tci <= tc; tci++) {
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int source = 0;
    int sink = 1;
    nodes = 2;

    string sentence, word;

    getline(cin, sentence);
    stringstream ss1(sentence);
    while (ss1 >> word) {
      if (!eng_words.count(word) && is_new(word)) {
        word_node.insert({ word, nodes });
        eng_words.insert(word);
        add_edge(nodes, nodes + 1, 1);
        add_edge(source, nodes, INF);
        nodes += 2;
      }
    }

    getline(cin, sentence);
    stringstream ss2(sentence);
    while (ss2 >> word) {
      if (!fre_words.count(word)) {
        if (is_new(word)) {
          word_node.insert({ word, nodes });
          fre_words.insert(word);
          add_edge(nodes, nodes + 1, 1);
          add_edge(nodes + 1, sink, INF);
          nodes += 2;
        } else {
          add_edge(word_node[word] + 1, sink, INF);
        }
      }
    }

    for (int i = 0; i < n - 2; i++) {
      getline(cin, sentence);
      stringstream ss(sentence);
      
      vector<string> words;
      unordered_set<string> cur_words;

      while (ss >> word) {
        if (is_new(word)) {
          word_node[word] = nodes;
          add_edge(nodes, nodes + 1, 1);
          nodes += 2;
        }

        if (!cur_words.count(word)) {
          words.push_back(word);
          cur_words.insert(word);
        }
      }

      for (int i = 0; i < (int)words.size(); i++) {
        for (int j = 0; j < i; j++) {
          int ni = word_node[words[i]];
          int nj = word_node[words[j]];
          add_edge(ni + 1, nj, INF);
          add_edge(nj + 1, ni, INF);
        }
      }
    }

    int mf = max_flow(source, sink);
    cout << "Case #" << tci << ": " << mf << '\n';

    for (int i = 0; i < nodes; i++) graph[i].clear();
    word_node.clear();
    eng_words.clear();
    fre_words.clear();
  }
}