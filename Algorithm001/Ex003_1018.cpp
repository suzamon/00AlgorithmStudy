/*
MN개의 단위 정사각형으로 나뉜 보드 검은색 혹은 흰색

체스판 검, 흰 번갈아서 칠해져야 -> 각 칸이 검은색 or 흰색 하나로 & 변을 공유하는 두개의 사각형은 다른색으로
8*8 크기의 체스판 자르고 다시 칠함 -> 아무데서나 골라도 됨, 다시 칠해야하는 정사각형의 최소 갯수
N, M 8<=N,M <=50


1. Input() : Answer, N, M, map[51][51]

2. Solve() :
	1) 0~ N-8 / 0 ~ M-8까지 탐색
	2) findCnt(int r, int c, int color) 각 부분별로 색칠해야하는 수 cnt 검색
		i=r; i<r+8; i++ & j=c;j<c+8; j++ -> (color == map[i][j]) cnt++ -> color 변경
*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, M, Answer = 64;
int map[51][51];

bool inside(int r, int c) {
	return r >= 0 && r < N && c >= 0 && c < M;
}

void findCnt(int r, int c, int color, int cnt) {
	for (int i = r; i < r + 8; i++) {
		for (int j = c; j < c + 8; j++) {
			if (i == r && j == c) continue;

			if (color == map[i][j]) {
				cnt++;
			}

			if (j == c + 7) break;

			if (color == 0) color = 1;
			else color = 0;
		}
	}

	Answer = min(Answer, cnt);
}

void Solution() {
	int color;
	for (int i = 0; i <= N - 8; i++) {
		for (int j = 0; j <= M - 8; j++) {
			color = map[i][j];
			findCnt(i, j, color, 0);
			if (color == 1) {
				map[i][j] = 0;
				findCnt(i, j, 0, 1);
				map[i][j] = 1;
			}
			else {
				map[i][j] = 1;
				findCnt(i, j, 1, 1);
				map[i][j] = 0;
			}
		}
	}
}

void Input() {
	string tmp;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		for (int j = 0; j < M; j++) {
			if (tmp.at(j) == 'B') map[i][j] = 0;
			else if(tmp.at(j) == 'W') map[i][j] = 1;
		}
	}
}


int main(void) {
	Input();
	Solution();
	cout << Answer << endl;
	return 0;
}