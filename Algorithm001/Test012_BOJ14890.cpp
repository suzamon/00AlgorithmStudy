/*
크기가 N×N인 지도가 있다. 지도의 각 칸에는 그 곳의 높이가 적혀져 있다.

오늘은 이 지도에서 지나갈 수 있는 길이 몇 개 있는지 알아보려고 한다.
길이란 한 행 또는 한 열 전부를 나타내며, 한쪽 끝에서 다른쪽 끝까지 지나가는 것이다.

다음과 같은 N=6인 경우 지도를 살펴보자.

이때, 길은 총 2N개가 있으며, 아래와 같다.

길을 지나갈 수 있으려면 길에 속한 모든 칸의 높이가 모두 같아야 한다. 또는, 경사로를 놓아서 지나갈 수 있는 길을 만들 수 있다
경사로는 높이가 항상 1이며, 길이는 L이다. 또, 개수는 매우 많아 부족할 일이 없다.
경사로는 낮은 칸과 높은 칸을 연결하며, 아래와 같은 조건을 만족해야한다.

경사로는 낮은 칸에 놓으며, L개의 연속된 칸에 경사로의 바닥이 모두 접해야 한다.
낮은 칸과 높은 칸의 높이 차이는 1이어야 한다.
경사로를 놓을 낮은 칸의 높이는 모두 같아야 하고, L개의 칸이 연속되어 있어야 한다.

아래와 같은 경우에는 경사로를 놓을 수 없다.

경사로를 놓은 곳에 또 경사로를 놓는 경우
낮은 칸과 높은 칸의 높이 차이가 1이 아닌 경우
낮은 지점의 칸의 높이가 모두 같지 않거나, L개가 연속되지 않은 경우
경사로를 놓다가 범위를 벗어나는 경우

가장 위에 주어진 그림 예의 경우에 지나갈 수 있는 길은 파란색으로, 지나갈 수 없는 길은 빨간색으로 표시되어 있으며,
아래와 같다. 경사로의 길이 L = 2이다.

지도가 주어졌을 때, 지나갈 수 있는 길의 개수를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N (2 ≤ N ≤ 100)과 L (1 ≤ L ≤ N)이 주어진다. 둘째 줄부터 N개의 줄에 지도가 주어진다.
각 칸의 높이는 10보다 작거나 같은 자연수이다.

출력
첫째 줄에 지나갈 수 있는 길의 개수를 출력한다.


1. Input()
	N, L, map[N][N][2], rotMap[N][N][2]

2. Solution() -> map과 rotMap 둘다 진행
	1) 각 행마다 진행
	2) 오른쪽으로 탐색(0~N-1까지 진행) -> 각 열 비교
	3) curH, nextH 차이 비교
		3-1) 0이면 다음칸 바로 진행
		3-2) 0이 아니면, curH와 nextH 크기 비교
			3-2-1) curH > nextH면, nextH <= col < nextH + L까지
					 map[row][col][1] == 0 && map[row][nextH][0] == map[row][col][0]이 맞는지 비교
					-> 조건 만족하면 [1]값 셋팅, 불만족이면 0 반환
					-> 최종으로 만족하면 다음 curH = nextH + L -1부터 시작
			3-2-2) curH < nextH면, curH - L < col <= curH 까지
					 map[row][col][1] == 0 && map[row][curH][0] == map[row][col][0]이 맞는지 비교
					-> 조건 만족하면 [1]값 셋팅, 불만족이면 0 반환
					-> 최종으로 만족하면 다음 curH = nextH부터 시작
	4) 끝가지 탐색 완료하면 1 반환
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, L, Answer = 0;
int map[101][101][2], rotMap[101][101][2];

int check_rot_row(int row) {
	int ret = 1, curH, nextH;

	for (int i = 0; i < N - 1; i++) {
		curH = rotMap[row][i][0];
		nextH = rotMap[row][i + 1][0];
		if (curH == nextH) continue;
		else if (curH - nextH == 1) {
			if (i + L >= N) return 0;
			for (int col = i + 1; col <= i + L; col++) {
				if (rotMap[row][col][1] == 0 && rotMap[row][col][0] == nextH) {
					rotMap[row][col][1] = 1;
				}
				else return 0;
			}
			i = i + L - 1;
		}
		else if (nextH - curH == 1) {
			if (i - L + 1 < 0) return 0;
			for (int col = i; col > i - L; col--) {
				if (rotMap[row][col][1] == 0 && rotMap[row][col][0] == curH) {
					rotMap[row][col][1] = 1;
				}
				else return 0;
			}
		}
		else return 0;
	}

	return 1;
}

int check_row(int row) {
	int ret = 1, curH, nextH;

	for (int i = 0; i < N - 1; i++) {
		curH = map[row][i][0];
		nextH = map[row][i + 1][0];
		if (curH == nextH) continue;
		else if (curH - nextH == 1) {
			if (i + L >= N) return 0;
			for (int col = i + 1; col <= i + L; col++) {
				if (map[row][col][1] == 0 && map[row][col][0] == nextH) {
					map[row][col][1] = 1;
				}
				else return 0;
			}
			i = i + L - 1;
		}
		else if (nextH - curH == 1) {
			if (i - L + 1 < 0) return 0;
			for (int col = i; col > i - L; col--) {
				if (map[row][col][1] == 0 && map[row][col][0] == curH) {
					map[row][col][1] = 1;
				}
				else return 0;
			}
		}
		else return 0;
	}

	return 1;
}

void Solution() {
	Answer = 0;

	//cout << "기존 맵 비교" << endl;
	for (int row = 0; row < N; row++) {
		if (check_row(row) == 1) {
			//cout << row + 1 << "행 조건 성립" << endl;
			Answer++;
		}
	}
	//cout << "회전 맵 비교" << endl;
	for (int row = 0; row < N; row++) {
		if (check_rot_row(row) == 1) {
			//cout << row + 1 << "행 조건 성립" << endl;
			Answer++;
		}
	}
}

void rot_map() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			rotMap[i][j][0] = map[j][i][0];
			rotMap[i][j][1] = 0;
		}
	}
}

void Input() {
	cin >> N >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j][0];
			map[i][j][1] = 0;
		}
	}
	rot_map();
}


int main(void) {
	Input();
	Solution();
	cout << Answer << endl;
	return 0;
}