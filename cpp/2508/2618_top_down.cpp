#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

int N, W;
Point incidents[1002];
int dp[1002][1002]; // dp[p1][p2]: 경찰차1이 p1, 경찰차2가 p2 사건을 마지막으로 처리했을 때의 남은 거리 최솟값

// 두 지점 사이의 거리를 계산하는 함수
int get_dist(Point p1, Point p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

// 경로를 추적하는 함수
void reconstruct_path(int p1_idx, int p2_idx) {
    if (p1_idx == W || p2_idx == W) {
        return;
    }

    int next_incident_idx = max(p1_idx, p2_idx) + 1;

    Point p1_loc = (p1_idx == 0) ? Point{1, 1} : incidents[p1_idx];
    Point p2_loc = (p2_idx == 0) ? Point{N, N} : incidents[p2_idx];

    int dist1 = get_dist(p1_loc, incidents[next_incident_idx]);
    int dist2 = get_dist(p2_loc, incidents[next_incident_idx]);

    if (dp[next_incident_idx][p2_idx] + dist1 < dp[p1_idx][next_incident_idx] + dist2) {
        cout << 1 << '\n';
        reconstruct_path(next_incident_idx, p2_idx);
    } else {
        cout << 2 << '\n';
        reconstruct_path(p1_idx, next_incident_idx);
    }
}

// DP를 이용해 최소 이동 거리를 계산하는 재귀 함수
int solve(int p1_idx, int p2_idx) {
    // 모든 사건을 처리한 경우
    if (p1_idx == W || p2_idx == W) {
        return 0;
    }

    // 이미 계산된 값이 있다면 반환
    if (dp[p1_idx][p2_idx] != -1) {
        return dp[p1_idx][p2_idx];
    }

    // 다음에 처리할 사건 번호
    int next_incident_idx = max(p1_idx, p2_idx) + 1;

    // 경찰차 1, 2의 현재 위치
    // idx가 0이면 초기 위치, 아니면 해당 사건의 위치
    Point p1_loc = (p1_idx == 0) ? Point{1, 1} : incidents[p1_idx];
    Point p2_loc = (p2_idx == 0) ? Point{N, N} : incidents[p2_idx];

    // Case 1: 경찰차 1이 다음 사건을 처리
    int dist1 = get_dist(p1_loc, incidents[next_incident_idx]);
    int result1 = solve(next_incident_idx, p2_idx) + dist1;

    // Case 2: 경찰차 2가 다음 사건을 처리
    int dist2 = get_dist(p2_loc, incidents[next_incident_idx]);
    int result2 = solve(p1_idx, next_incident_idx) + dist2;

    // 더 작은 값을 DP 테이블에 저장하고 반환
    return dp[p1_idx][p2_idx] = min(result1, result2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> W;
    for (int i = 1; i <= W; ++i) {
        cin >> incidents[i].x >> incidents[i].y;
    }

    // DP 테이블 초기화 (-1은 아직 계산되지 않았음을 의미)
    for (int i = 0; i < 1002; ++i) {
        for (int j = 0; j < 1002; ++j) {
            dp[i][j] = -1;
        }
    }

    // 최소 이동 거리 출력
    cout << solve(0, 0) << '\n';
    
    // 경로 추적 및 출력
    reconstruct_path(0, 0);

    return 0;
}