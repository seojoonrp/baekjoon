#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
  int index;
  int value;
};

int n;
int a[1000002];

// lis에 저장될 때 전 원소의 a상 인덱스가 뭐였냐. 맨 처음으로 들어왔으면 -1
int prevIdx[1000002];

// temp Lis가 실제와 달라지는 경우 : 기존 lis의 값보다 더 작은 값이 들어와서 교체될 때
vector<Node> lis_temp;
vector<int> lis;

// lower bound 찾기
int findLowerBound(const int& x) {
  int start = 0;
  int end = lis_temp.size();
  int mid;

  while (start < end) {
    mid = (start + end) / 2;

    if (lis_temp[mid].value >= x) end = mid;
    else start = mid + 1;
  }

  return end;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i];

  // 초기값 설정
  lis_temp.push_back({0, a[0]});
  prevIdx[0] = -1;

  for (int i = 1; i < n; ++i) {
    // 자기 이상인 값이 처음 나오는 인덱스
    int idx = findLowerBound(a[i]);

    // 길이만 구할 때 했던 것. 근데 이제 인덱스도 저장함
    if (idx == lis_temp.size()) {
      lis_temp.push_back({i, a[i]});
    }
    else {
      lis_temp[idx] = {i, a[i]};
    }

    // prevIdx 구하기
    // 맨 처음이면 -1이고, 아니라면 얘가 들어간 곳 바로 전 원소(idx - 1번 원소)의 인덱스를 저장한다.
    if (idx > 0) prevIdx[i] = lis_temp[idx - 1].index;
    else prevIdx[i] = -1;
  }

  // 어차피 temp lis의 마지막 원소는 실제 lis의 마지막 원소와 같다. 물론 lis가 유일하지 않은 상황이라면 다르게 집을 수도 있긴 함
  // 이게 중요하다. 결국 이 짓을 할 수 있는 원리가 "어떤 원소를 골랐을 때, 그 전 원소가 앞쪽 temp lis의 대빵임은 확실하다"이기 때문이다.
  // 그러니까 그냥 prevIdx 값을 받아와서 계속 갱신하면 역추적이 되는거임
  int cur = lis_temp.back().index;

  // 맨 앞 원소를 만나서, 그 전에 원소가 없는 경우(prevIdx가 -1인 경우)까지 반복
  while (cur != -1) {
    lis.push_back(a[cur]);

    // 앞쪽 temp lis가 지랄난건 중요하지 않다.
    // 중요한 건 prevIdx의 원소가 그들 중 대빵이라는 것. 그렇기에 앞쪽 실제 lis의 마지막 원소는 어차피 얘다.
    // 정확히 말하자면, prevIdx의 원소는 앞쪽 lis의 끝에 추가할 수 있는 유일한 후보군 중 하나인 것
    cur = prevIdx[cur];
  }
  reverse(lis.begin(), lis.end());

  cout << lis.size() << "\n";
  for (auto& val : lis) cout << val << " ";
  cout << "\n";
}