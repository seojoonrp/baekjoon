#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n;
int board[21][21];
int ans = 0;

void combine(vector<int>& line) {
  vector<int> combined;
  
  for (int i = 0; i < n; ++i) {
    if (line[i] != 0) combined.push_back(line[i]);
  }
  line.clear();

  for (int i = 0; i < combined.size(); ++i) {
    if ((i != combined.size() - 1) && combined[i] == combined[i + 1]) {
      line.push_back(combined[i] * 2);
      ++i;
    } else {
      line.push_back(combined[i]);
    }
  }

  while (line.size() < n) line.push_back(0);
}

// 0, 1, 2, 3 -> left, right, up, down
void moveBoard(int dir) {
  for (int i = 0; i < n; ++i) {
    vector<int> line;

    for (int j = 0; j < n; ++j) {
      if (dir == 0) line.push_back(board[i][j]);
      else if (dir == 1) line.push_back(board[i][n - 1 - j]);
      else if (dir == 2) line.push_back(board[j][i]);
      else if (dir == 3) line.push_back(board[n - 1 - j][i]);
    }

    combine(line);

    for (int j = 0; j < n; ++j) {
      if (dir == 0) board[i][j] = line[j];
      else if (dir == 1) board[i][n - 1 - j] = line[j];
      else if (dir == 2) board[j][i] = line[j];
      else if (dir == 3) board[n - 1 - j][i] = line[j];
    }
  }
}

void solve(int movenum) {

  if (movenum == 5) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) ans = max(ans, board[i][j]);
    }
    return;
  }

  int backup[21][21];
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) backup[i][j] = board[i][j];
  }

  for (int dir : {0, 1, 2, 3}) {
    moveBoard(dir);
    solve(movenum + 1);
    
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j)  board[i][j] = backup[i][j];
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) cin >> board[i][j];
  }

  solve(0);

  cout << ans << '\n';
}