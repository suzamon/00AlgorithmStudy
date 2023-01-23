/*
색종이 1x1, 2x2, 3x3, 4x4, 5x5 -> 10x10인 종이 위에 색종이 붙임 & 각 종류의 색종이는 5개씩
각각의 칸에 0, 1로 적혀져있고 모두 색종이로 덮여져야한다. 0이 적힌 칸에는 색종이가 있으면 안 된다.
1이 적힌 모든 칸을 붙이는데 필요한 색종이의 최소 개수 -> Answer / 불가한 경우 -1 출력


1. Input() : map[11][11], Answer, colorSize[6]

2. Solution():
	1) Answer = 0 부터 시작
	2) (0,0) ~ (9,9) 까지 차례대로 DFS 해야한다

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