/*
������ 1x1, 2x2, 3x3, 4x4, 5x5 -> 10x10�� ���� ���� ������ ���� & �� ������ �����̴� 5����
������ ĭ�� 0, 1�� �������ְ� ��� �����̷� ���������Ѵ�. 0�� ���� ĭ���� �����̰� ������ �� �ȴ�.
1�� ���� ��� ĭ�� ���̴µ� �ʿ��� �������� �ּ� ���� -> Answer / �Ұ��� ��� -1 ���


1. Input() : map[11][11], Answer, colorSize[6]

2. Solution():
	1) Answer = 0 ���� ����
	2) (0,0) ~ (9,9) ���� ���ʴ�� DFS �ؾ��Ѵ�

*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, Answer = 26;
int map[11][11] = { 0, };
int colorSize[6] = { 5, };

deque <pair <int, int>> onePos;

bool inside(int x, int y) {
	return x >= 0 && x < 10 && y >= 0 && y < 10;
}

bool check(int startX, int startY, int size) {
	for (int i = startX; i < startX + size; i++) {
		for (int j = startY; j < startY + size; j++) {
			if (!inside(i, j) || map[i][j] != 1) return false;
		}
	}
	return true;
}

void editMap(int startX, int startY, int size, int state) {
	for (int i = startX; i < startX + size; i++) {
		for (int j = startY; j < startY + size; j++) {
			map[i][j] = state;	
		}
	}
}

void DFS(int startX, int startY, int cnt) {
	if (startX >= N - 1 && startY >= N) {
		Answer = min(Answer, cnt);
	}

	if (Answer <= cnt) return;

	if (startY > 9) {
		DFS(startX + 1, 0, cnt);
		return;
	}

	if (map[startX][startY] == 1) {
		for (int cSize = 5; cSize >= 1; cSize--) {
			if (colorSize[cSize] > 0 && check(startX, startY, cSize)) {
				editMap(startX, startY, cSize, 0);
				colorSize[cSize]--;
				DFS(startX, startY + 1, cnt+1);
				colorSize[cSize]++;
				editMap(startX, startY, cSize, 1);
			}
		}

	}
	else DFS(startX, startY + 1, cnt);

}


void Solution() {
	
	DFS(0, 0, 0);
}

void Input() {
	N = 10;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) onePos.push_back(make_pair(i, j));
		}
	}
	for (int i = 1; i < 6; i++) {
		colorSize[i] = 5;
	}
	return;
}

int main(void) {
	Input();
	Solution();
	if (Answer == 26) Answer = -1;
	cout << Answer << endl;
	return 0;
}