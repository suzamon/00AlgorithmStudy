/*
폴리오미노란 크기가 1×1인 정사각형을 여러 개 이어서 붙인 도형이며, 다음과 같은 조건을 만족해야 한다.

정사각형은 서로 겹치면 안 된다.
도형은 모두 연결되어 있어야 한다.
정사각형의 변끼리 연결되어 있어야 한다. 즉, 꼭짓점과 꼭짓점만 맞닿아 있으면 안 된다

크기가 N×M인 종이 위에 테트로미노 하나를 놓으려고 한다. 종이는 1×1 크기의 칸으로 나누어져 있으며, 각각의 칸에는 정수

테트로미노 하나를 적절히 놓아서 테트로미노가 놓인 칸에 쓰여 있는 수들의 합을 최대로 하는 프로그램을 작성하시오.

테트로미노는 반드시 한 정사각형이 정확히 하나의 칸을 포함하도록 놓아야 하며, 회전이나 대칭을 시켜도 된다.

첫째 줄에 종이의 세로 크기 N과 가로 크기 M이 주어진다. (4 ≤ N, M ≤ 500)

둘째 줄부터 N개의 줄에 종이에 쓰여 있는 수가 주어진다.
i번째 줄의 j번째 수는 위에서부터 i번째 칸, 왼쪽에서부터 j번째 칸에 쓰여 있는 수이다.
입력으로 주어지는 수는 1,000을 넘지 않는 자연수이다.

A) 첫째 줄에 테트로미노가 놓인 칸에 쓰인 수들의 합의 최댓값을 출력한다.

1. Input
	N, M, map[N][M]
2. Solution
	1) 4개 1x1 정사각형을 만든 폴리오미노 저장
		: 아래, 오른 이동하는 폴리오미노만 저장
		: 저장된 4개의 폴리오미노는 dq에 저장
	2) (0,0) ~ (N,M)까지 탐색


*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, M, Answer = 0;
int map[501][501];
int arr[9][9] = { 0, };

int pointDx[4];
int pointDy[4];
deque <pair<int, int>> dq;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

void print_poly_map() {
	int cnt = 1;
	while (!dq.empty()) {
		int pmap[9][9] = { 0, };

		for (int i = 0; i < 4; i++) {
			pmap[4 + dq.front().first][ 4 + dq.front().second] = 1;
			dq.pop_front();
		}

		cout << cnt << "번째 폴리" << endl;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cout << pmap[i][j] << ' ';
			}
			cout << endl;
		}
		cout << endl;
		cnt++;
	}
}

void find_answer() {
	int polyArr[4][2] = { 0, };
	int polyCnt = dq.size() / 4;
	int nextX, nextY, sum, exitFlag;

	for (int startX = 0; startX < N; startX++) {
		for (int startY = 0; startY < M; startY++) {
			for (int i = 0; i < polyCnt; i++) {
				sum = 0;
				exitFlag = 0;
				for (int j = 0; j < 4; j++) {
					polyArr[j][0] = dq[(i * 4) + j].first;
					polyArr[j][1] = dq[(i * 4) + j].second;
					nextX = startX + polyArr[j][0];
					nextY = startY + polyArr[j][1];
					if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) {
						exitFlag = 1;
						break;
					}
					sum += map[nextX][nextY];
				}
				if (sum > Answer && exitFlag == 0) {
					Answer = sum;
					/*
					cout << Answer << "일 때" << endl;
					cout << "x: " << startX << ", y: " << startY << endl;
					cout << "ploy 맵" << endl;
					for (int k = 0; k < 4; k++) {
						cout << '(' << polyArr[k][0] << ',' << polyArr[k][1] << "), ";
					}
					cout << endl;
					cout << endl;
					*/
				}
			}


		}
	}

}

void find_poly(int cnt) {
	if (cnt == 0) {
		pointDx[0] = 0;
		pointDy[0] = 0;
		arr[4][4] = 1;
		find_poly(1);
	}
	else if (cnt == 4) {
		for (int i = 0; i < 4; i++) dq.push_back(make_pair(pointDx[i], pointDy[i]));
		return;
	}

	int curX, curY, nextX, nextY;

	for (int i = 0; i < cnt; i++) {
		curX = pointDx[i];
		curY = pointDy[i];

		for (int d = 0; d < 4; d++) {
			nextX = curX + dx[d];
			nextY = curY + dy[d];
			if (arr[4 + nextX][4 + nextY] == 0) {
				pointDx[cnt] = nextX;
				pointDy[cnt] = nextY;
				arr[4 + nextX][4 + nextY] = 1;
				find_poly(cnt + 1);
				arr[4 + nextX][4 + nextY] = 0;
			}
		}
	}

}

void Solution() {
	find_poly(0);
	find_answer();
}

void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
}


int main(void) {
	/*
	int T;

	cin >> T;
	for (int i = 0; i < T; i++) {
		Answer = 0;
		Input();
		Solution();
		cout << Answer << endl;
	}
	*/
	//find_poly(0);
	//print_poly_map();
	
	Input();
	Solution();
	cout << Answer << endl;
	
	return 0;
}