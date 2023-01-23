/*
MN���� ���� ���簢������ ���� ���� ������ Ȥ�� ���

ü���� ��, �� �����Ƽ� ĥ������ -> �� ĭ�� ������ or ��� �ϳ��� & ���� �����ϴ� �ΰ��� �簢���� �ٸ�������
8*8 ũ���� ü���� �ڸ��� �ٽ� ĥ�� -> �ƹ������� ��� ��, �ٽ� ĥ�ؾ��ϴ� ���簢���� �ּ� ����
N, M 8<=N,M <=50


1. Input() : Answer, N, M, map[51][51]

2. Solve() :
	1) 0~ N-8 / 0 ~ M-8���� Ž��
	2) findCnt(int r, int c, int color) �� �κк��� ��ĥ�ؾ��ϴ� �� cnt �˻�
		i=r; i<r+8; i++ & j=c;j<c+8; j++ -> (color == map[i][j]) cnt++ -> color ����
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