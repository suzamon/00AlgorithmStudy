#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <deque>

using namespace std;

int N;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };

int map[501][501]; //(1,1)부터 시작
int to[2];
int Answer = 0;


void print_map() {
	cout << "맵" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void move_sand(int sand, int dir, int startX, int startY) {
	int nextX, nextY, nextSand = 0, moveSand = 0;

	switch (dir) {
	case 0:
		nextX = startX - 2;
		nextY = startY;
		nextSand = (int)(sand * 0.02);
		moveSand += nextSand;
		if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
			Answer += nextSand;
		}
		else {
			map[nextX][nextY] += nextSand;
		}

		for (int i = -1; i <= 1; i++) {
			nextX = startX - 1;
			nextY = startY + i;

			if (i == -1) nextSand = (int)(sand * 0.1);
			else if (i == 0) nextSand = (int)(sand * 0.07);
			else if (i == 1) nextSand = (int)(sand * 0.01);
			moveSand += nextSand;

			if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
				Answer += nextSand;
			}
			else {
				map[nextX][nextY] += nextSand;
			}
		}

		for (int i = -1; i <= 1; i++) {
			nextX = startX + 1;
			nextY = startY + i;

			if (i == -1) nextSand = (int)(sand * 0.1);
			else if (i == 0) nextSand = (int)(sand * 0.07);
			else if (i == 1) nextSand = (int)(sand * 0.01);
			moveSand += nextSand;

			if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
				Answer += nextSand;
			}
			else {
				map[nextX][nextY] += nextSand;
			}
		}

		nextX = startX + 2;
		nextY = startY;
		nextSand = (int)(sand * 0.02);
		moveSand += nextSand;
		if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
			Answer += nextSand;
		}
		else {
			map[nextX][nextY] += nextSand;
		}

		nextX = startX;
		nextY = startY - 2;
		nextSand = (int)(sand * 0.05);
		moveSand += nextSand;
		if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
			Answer += nextSand;
		}
		else {
			map[nextX][nextY] += nextSand;
		}

		nextX = startX;
		nextY = startY - 1;
		nextSand = sand - moveSand;
		if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
			Answer += nextSand;
		}
		else {
			map[nextX][nextY] += nextSand;
		}

		break;
	case 1:
		nextX = startX;
		nextY = startY - 2;
		nextSand = (int)(sand * 0.02);
		moveSand += nextSand;
		if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
			Answer += nextSand;
		}
		else {
			map[nextX][nextY] += nextSand;
		}

		for (int i = -1; i <= 1; i++) {
			nextX = startX + i;
			nextY = startY - 1;

			if (i == 1) nextSand = (int)(sand * 0.1);
			else if (i == 0) nextSand = (int)(sand * 0.07);
			else if (i == -1) nextSand = (int)(sand * 0.01);
			moveSand += nextSand;

			if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
				Answer += nextSand;
			}
			else {
				map[nextX][nextY] += nextSand;
			}
		}

		for (int i = -1; i <= 1; i++) {
			nextX = startX + i;
			nextY = startY + 1;

			if (i == 1) nextSand = (int)(sand * 0.1);
			else if (i == 0) nextSand = (int)(sand * 0.07);
			else if (i == -1) nextSand = (int)(sand * 0.01);
			moveSand += nextSand;

			if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
				Answer += nextSand;
			}
			else {
				map[nextX][nextY] += nextSand;
			}
		}

		nextX = startX;
		nextY = startY + 2;
		nextSand = (int)(sand * 0.02);
		moveSand += nextSand;
		if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
			Answer += nextSand;
		}
		else {
			map[nextX][nextY] += nextSand;
		}

		nextX = startX + 2;
		nextY = startY;
		nextSand = (int)(sand * 0.05);
		moveSand += nextSand;
		if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
			Answer += nextSand;
		}
		else {
			map[nextX][nextY] += nextSand;
		}

		nextX = startX + 1;
		nextY = startY;
		nextSand = sand - moveSand;
		if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
			Answer += nextSand;
		}
		else {
			map[nextX][nextY] += nextSand;
		}
		break;
	case 2:
		nextX = startX - 2;
		nextY = startY;
		nextSand = (int)(sand * 0.02);
		moveSand += nextSand;
		if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
			Answer += nextSand;
		}
		else {
			map[nextX][nextY] += nextSand;
		}

		for (int i = -1; i <= 1; i++) {
			nextX = startX - 1;
			nextY = startY + i;

			if (i == 1) nextSand = (int)(sand * 0.1);
			else if (i == 0) nextSand = (int)(sand * 0.07);
			else if (i == -1) nextSand = (int)(sand * 0.01);
			moveSand += nextSand;

			if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
				Answer += nextSand;
			}
			else {
				map[nextX][nextY] += nextSand;
			}
		}

		for (int i = -1; i <= 1; i++) {
			nextX = startX + 1;
			nextY = startY + i;

			if (i == 1) nextSand = (int)(sand * 0.1);
			else if (i == 0) nextSand = (int)(sand * 0.07);
			else if (i == -1) nextSand = (int)(sand * 0.01);
			moveSand += nextSand;

			if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
				Answer += nextSand;
			}
			else {
				map[nextX][nextY] += nextSand;
			}
		}

		nextX = startX + 2;
		nextY = startY;
		nextSand = (int)(sand * 0.02);
		moveSand += nextSand;
		if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
			Answer += nextSand;
		}
		else {
			map[nextX][nextY] += nextSand;
		}

		nextX = startX;
		nextY = startY + 2;
		nextSand = (int)(sand * 0.05);
		moveSand += nextSand;
		if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
			Answer += nextSand;
		}
		else {
			map[nextX][nextY] += nextSand;
		}

		nextX = startX;
		nextY = startY + 1;
		nextSand = sand - moveSand;
		if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
			Answer += nextSand;
		}
		else {
			map[nextX][nextY] += nextSand;
		}

		break;
	case 3:
		nextX = startX;
		nextY = startY - 2;
		nextSand = (int)(sand * 0.02);
		moveSand += nextSand;
		if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
			Answer += nextSand;
		}
		else {
			map[nextX][nextY] += nextSand;
		}

		for (int i = -1; i <= 1; i++) {
			nextX = startX + i;
			nextY = startY - 1;

			if (i == -1) nextSand = (int)(sand * 0.1);
			else if (i == 0) nextSand = (int)(sand * 0.07);
			else if (i == 1) nextSand = (int)(sand * 0.01);
			moveSand += nextSand;

			if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
				Answer += nextSand;
			}
			else {
				map[nextX][nextY] += nextSand;
			}
		}

		for (int i = -1; i <= 1; i++) {
			nextX = startX + i;
			nextY = startY + 1;

			if (i == -1) nextSand = (int)(sand * 0.1);
			else if (i == 0) nextSand = (int)(sand * 0.07);
			else if (i == 1) nextSand = (int)(sand * 0.01);
			moveSand += nextSand;

			if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
				Answer += nextSand;
			}
			else {
				map[nextX][nextY] += nextSand;
			}
		}

		nextX = startX;
		nextY = startY + 2;
		nextSand = (int)(sand * 0.02);
		moveSand += nextSand;
		if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
			Answer += nextSand;
		}
		else {
			map[nextX][nextY] += nextSand;
		}

		nextX = startX - 2;
		nextY = startY;
		nextSand = (int)(sand * 0.05);
		moveSand += nextSand;
		if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
			Answer += nextSand;
		}
		else {
			map[nextX][nextY] += nextSand;
		}

		nextX = startX - 1;
		nextY = startY;
		nextSand = sand - moveSand;
		if (nextX <1 || nextX >N || nextY<1 || nextY >N) {
			Answer += nextSand;
		}
		else {
			map[nextX][nextY] += nextSand;
		}
		break;
	}
}

void move_to(int n) {
	int nextX, nextY;
	int nextSand;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < n; j++) {
			nextX = to[0] + dx[i];
			nextY = to[1] + dy[i];
			nextSand = map[nextX][nextY];
			//cout << "nextX: " << nextX << ", nextY: " << nextY << ", dir: "<<i<<endl;
			if (nextSand > 0) {
				move_sand(nextSand, i, nextX, nextY);
				map[nextX][nextY] = 0;
				//print_map();
			}

			to[0] = nextX;
			to[1] = nextY;
		}
	}
	for (int i = 2; i < 4; i++) {
		for (int j = 0; j < n + 1; j++) {
			nextX = to[0] + dx[i];
			nextY = to[1] + dy[i];
			nextSand = map[nextX][nextY];
			//cout << "nextX: " << nextX << ", nextY: " << nextY << ", dir: " << i << endl;
			if (nextSand > 0) {
				move_sand(nextSand, i, nextX, nextY);
				map[nextX][nextY] = 0;
				//print_map();
			}

			to[0] = nextX;
			to[1] = nextY;
		}
	}

	if (n + 1 == N - 1) {
		for (int j = 0; j < n + 1; j++) {
			nextX = to[0] + dx[0];
			nextY = to[1] + dy[0];
			nextSand = map[nextX][nextY];
			//cout << "nextX: " << nextX << ", nextY: " << nextY << ", dir: " << 0 << endl;
			if (nextSand > 0) {
				move_sand(nextSand, 0, nextX, nextY);
				map[nextX][nextY] = 0;
				//print_map();
			}
			to[0] = nextX;
			to[1] = nextY;
		}
	}

}

void Solve() {
	for (int i = 1; i <= N - 2; i += 2) {
		move_to(i);
	}
	cout << Answer << endl;
}

void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}
	to[0] = N / 2 + 1;
	to[1] = N / 2 + 1;
}

int main(void) {
	Input();
	//cout << "토네이도 시작 위치: " << to[0] << ", " << to[1] << endl;
	Solve();

	return 0;
}
