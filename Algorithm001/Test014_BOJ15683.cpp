/*
스타트링크의 사무실은 1×1크기의 정사각형으로 나누어져 있는 N×M 크기의 직사각형으로 나타낼 수 있다.
사무실에는 총 K개의 CCTV가 설치되어져 있는데, CCTV는 5가지 종류가 있다. 각 CCTV가 감시할 수 있는 방법은 다음과 같다.

1번 CCTV는 한 쪽 방향만 감시할 수 있다. 2번과 3번은 두 방향을 감시할 수 있는데,
2번은 감시하는 방향이 서로 반대방향이어야 하고, 3번은 직각 방향이어야 한다. 4번은 세 방향, 5번은 네 방향을 감시할 수 있다.
CCTV는 감시할 수 있는 방향에 있는 칸 전체를 감시할 수 있다. 사무실에는 벽이 있는데, CCTV는 벽을 통과할 수 없다.
CCTV가 감시할 수 없는 영역은 사각지대라고 한다.
CCTV는 회전시킬 수 있는데, 회전은 항상 90도 방향으로 해야 하며, 감시하려고 하는 방향이 가로 또는 세로 방향이어야 한다.

지도에서 0은 빈 칸, 6은 벽, 1~5는 CCTV의 번호이다.

CCTV는 CCTV를 통과할 수 있다. 아래 예시를 보자.

사무실의 크기와 상태, 그리고 CCTV의 정보가 주어졌을 때, CCTV의 방향을 적절히 정해서,
사각 지대의 최소 크기를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 사무실의 세로 크기 N과 가로 크기 M이 주어진다. (1 ≤ N, M ≤ 8)
둘째 줄부터 N개의 줄에는 사무실 각 칸의 정보가 주어진다. 0은 빈 칸, 6은 벽, 1~5는 CCTV를 나타내고,
문제에서 설명한 CCTV의 종류이다.
CCTV의 최대 개수는 8개를 넘지 않는다.

출력
첫째 줄에 사각 지대의 최소 크기를 출력한다.

N, M, cctvCnt, map[8][8], cctv[8][4] -> x, y, cctv 종류, 방향

1. Input()
	N, M, map[N][M], cctv[8][2] (1~5)

2. Solution()
	1. cctvCnt만큼 DFS로 방향 정하기
		1, 3, 4 -> 0,1,2,3,4 방향
		2 -> 0,1 방향
		5 -> 0 방향
	2. cctvCnt면 시뮬레이션 ㄱㄱ
*/


#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, M, cctvCnt, emptyCnt, copyEmptyCnt, Answer = -1;
int map[9][9], copyMap[9][9], cctv[9][4];

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void print_cctv() {
	for (int i = 0; i < cctvCnt; i++) {
		cout << '(' << cctv[i][0] << ", " << cctv[i][1] << ")에 " << cctv[i][2] << "번 cctv 방향: " << cctv[i][3] << endl;
	}
	cout << endl;
}

void sim_cctv(int dir, int startX, int startY) {
	int nextX, nextY;

	while (1) {
		nextX = startX + dx[dir];
		nextY = startY + dy[dir];
		if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) break;

		if (copyMap[nextX][nextY] == 0) {
			copyEmptyCnt--;
			copyMap[nextX][nextY] = 7;
			startX = nextX;
			startY = nextY;
		}
		else if (copyMap[nextX][nextY] == 6) {
			break;
		}
		else {
			startX = nextX;
			startY = nextY;
		}
	}

}

void mark_cctv(int cctvNum, int startX, int startY, int dir) {
	int nextX, nextY;
	if (cctvNum == 1) {
		sim_cctv(dir, startX, startY);
	}
	else if (cctvNum == 2) {
		if (dir == 0) {
			sim_cctv(1, startX, startY);
			sim_cctv(3, startX, startY);
		}
		else {
			sim_cctv(0, startX, startY);
			sim_cctv(2, startX, startY);
		}
	}
	else if (cctvNum == 3) {
		if (dir == 3) {
			sim_cctv(dir, startX, startY);
			sim_cctv(0, startX, startY);
		}
		else {
			sim_cctv(dir, startX, startY);
			sim_cctv(dir + 1, startX, startY);
		}
	}
	else if (cctvNum == 4) {
		if (dir == 0) {
			sim_cctv(3, startX, startY);
			sim_cctv(0, startX, startY);
			sim_cctv(1, startX, startY);
		}
		else if (dir == 1) {
			sim_cctv(0, startX, startY);
			sim_cctv(1, startX, startY);
			sim_cctv(2, startX, startY);
		}
		else if (dir == 2) {
			sim_cctv(2, startX, startY);
			sim_cctv(3, startX, startY);
			sim_cctv(1, startX, startY);
		}
		else {
			sim_cctv(0, startX, startY);
			sim_cctv(2, startX, startY);
			sim_cctv(3, startX, startY);
		}
	}
	else {
		for (int d = 0; d < 4; d++) {
			sim_cctv(d, startX, startY);
		}
	}
}

void Simulation() {
	for (int i = 0; i < cctvCnt; i++) {
		mark_cctv(cctv[i][2], cctv[i][0], cctv[i][1], cctv[i][3]);
	}

	if (Answer == -1) Answer = copyEmptyCnt;
	else if (Answer > copyEmptyCnt) Answer = copyEmptyCnt;
}

void copy_map() {
	copyEmptyCnt = emptyCnt;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			copyMap[i][j] = map[i][j];
		}
	}
}

void DFS(int cnt) {
	if (cnt == cctvCnt) {
		//print_cctv();
		copy_map();
		Simulation();
		return;
	}

	int cctvNum = cctv[cnt][2];
	if (Answer == 0) return;

	switch (cctvNum) {
	case 1:case 3: case 4:
		for (int i = 0; i < 4; i++) {
			cctv[cnt][3] = i;
			DFS(cnt + 1);
			if (Answer == 0) return;
		}
		break;
	case 2:
		for (int i = 0; i < 2; i++) {
			cctv[cnt][3] = i;
			DFS(cnt + 1);
			if (Answer == 0) return;
		}
		break;
	case 5:
		cctv[cnt][3] = 0;
		DFS(cnt + 1);
		if (Answer == 0) return;
		break;
	}
}

void Solution() {
	DFS(0);
}

void Input() {
	cctvCnt = 0;
	emptyCnt = 0;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] > 0 && map[i][j] < 6) {
				cctv[cctvCnt][0] = i;
				cctv[cctvCnt][1] = j;
				cctv[cctvCnt][2] = map[i][j];
				cctvCnt++;
			}
			else if (map[i][j] == 0) emptyCnt++;
		}
	}
}

int main(void) {
	Input();
	Solution();
	cout << Answer << endl;
	return 0;
}