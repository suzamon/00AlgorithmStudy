#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int R, C, T, Answer = 0;

int map[51][51];
int airCondi[2][2];

deque <pair <int, pair <int, int>>> a;

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void print_map() {
	cout << "Map" << endl;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;

}

void find_sum() {
	Answer = 0;
	int initSize = a.size();

	for (int i = 0; i < initSize; i++) {
		Answer += a.front().first;
		a.pop_front();
	}
}


void add_deque() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (map[i][j] > 0) {
				a.push_back(make_pair(map[i][j], make_pair(i, j)));
			}
		}
	}
}

void air_circulate() {
	int startX, startY, nextX, nextY, start, next, d;
	int nextArr[51];

	startX = airCondi[0][0];
	startY = airCondi[0][1] + 1;
	start = map[startX][startY];
	map[startX][startY] = 0;
	// ℃ 规氢 (1);
	d = 1;
	while (1) {
		nextX = startX;
		nextY = startY + dy[d];
		if (nextY == C - 1) {
			next = map[nextX][nextY];
			map[nextX][nextY] = start;
			start = next;
			startY = nextY;
			break;
		}
		next = map[nextX][nextY];
		map[nextX][nextY] = start;
		start = next;
		startY = nextY;
	}
	// ¤ 规氢 (0);
	d = 0;
	while (1) {
		nextX = startX + dx[d];
		nextY = startY;
		if (nextX == 0) {
			next = map[nextX][nextY];
			map[nextX][nextY] = start;
			start = next;
			startX = nextX;
			break;
		}
		next = map[nextX][nextY];
		map[nextX][nextY] = start;
		start = next;
		start = next;
		startX = nextX;
	}
	// ＄ 规氢 (3);
	d = 3;
	while (1) {
		nextX = startX;
		nextY = startY + dy[d];
		if (nextY == 0) {
			next = map[nextX][nextY];
			map[nextX][nextY] = start;
			start = next;
			startY = nextY;
			break;
		}
		next = map[nextX][nextY];
		map[nextX][nextY] = start;
		start = next;
		startY = nextY;
	}
	// ￠ 规氢 (2);
	d = 2;
	while (1) {
		nextX = startX + dx[d];
		nextY = startY;
		if (nextX == airCondi[0][0] - 1) {
			next = map[nextX][nextY];
			map[nextX][nextY] = start;
			start = next;
			startX = nextX;
			break;
		}
		next = map[nextX][nextY];
		map[nextX][nextY] = start;
		start = next;
		startX = nextX;
	}

	startX = airCondi[1][0];
	startY = airCondi[1][1] + 1;
	start = map[startX][startY];
	map[startX][startY] = 0;
	// ℃ 规氢 (1);
	d = 1;
	while (1) {
		nextX = startX;
		nextY = startY + dy[d];
		if (nextY == C - 1) {
			next = map[nextX][nextY];
			map[nextX][nextY] = start;
			start = next;
			startY = nextY;
			break;
		}
		next = map[nextX][nextY];
		map[nextX][nextY] = start;
		start = next;
		startY = nextY;
	}
	// ￠ 规氢 (2);
	d = 2;
	while (1) {
		nextX = startX + dx[d];
		nextY = startY;
		if (nextX == R-1) {
			next = map[nextX][nextY];
			map[nextX][nextY] = start;
			start = next;
			startX = nextX;
			break;
		}
		next = map[nextX][nextY];
		map[nextX][nextY] = start;
		start = next;
		start = next;
		startX = nextX;
	}
	// ＄ 规氢 (3);
	d = 3;
	while (1) {
		nextX = startX;
		nextY = startY + dy[d];
		if (nextY == 0) {
			next = map[nextX][nextY];
			map[nextX][nextY] = start;
			start = next;
			startY = nextY;
			break;
		}
		next = map[nextX][nextY];
		map[nextX][nextY] = start;
		start = next;
		startY = nextY;
	}
	// ¤ 规氢 (0);
	d = 0;
	while (1) {
		nextX = startX + dx[d];
		nextY = startY;
		if (nextX == airCondi[1][0] + 1) {
			next = map[nextX][nextY];
			map[nextX][nextY] = start;
			start = next;
			startX = nextX;
			break;
		}
		next = map[nextX][nextY];
		map[nextX][nextY] = start;
		start = next;
		startX = nextX;
	}

}

void air_spread() {
	int startX, startY, startAmount, nextX, nextY, nextCnt, nextAmount, initSize;

	initSize = a.size();
	for (int i = 0; i < initSize; i++) {
		startAmount = a.front().first;
		startX = a.front().second.first;
		startY = a.front().second.second;
		a.pop_front();

		if (startAmount < 5) continue;

		nextCnt = 0;
		nextAmount = startAmount / 5;


		map[startX][startY] = 0;
		for (int d = 0; d < 4; d++) {
			nextX = startX + dx[d];
			nextY = startY + dy[d];
			if (map[nextX][nextY] != -1 && nextX >= 0 && nextY >= 0 && nextX < R && nextY < C) {
				a.push_back(make_pair(nextAmount, make_pair(nextX, nextY)));
				nextCnt++;
			}
		}
		startAmount = startAmount - (nextAmount * nextCnt);
		a.push_back(make_pair(startAmount, make_pair(startX, startY)));
	}

	initSize = a.size();
	for (int i = 0; i < initSize; i++) {
		startAmount = a.front().first;
		startX = a.front().second.first;
		startY = a.front().second.second;
		a.pop_front();
		map[startX][startY] += startAmount;
	}

}

void Solve() {

	for (int time = 0; time < T; time++) {
		air_spread();
		//print_map();

		air_circulate();
		//print_map();

		add_deque();
	}

	find_sum();
}

void Input() {
	cin >> R >> C >> T;
	int airCondiCnt = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
			if (map[i][j] == -1) {
				airCondi[airCondiCnt][0] = i;
				airCondi[airCondiCnt][1] = j;
				airCondiCnt++;
			}
			else if (map[i][j] != 0) {
				a.push_back(make_pair(map[i][j], make_pair(i, j)));
			}
		}
	}
}

int main(void) {
	Input();
	Solve();
	cout << Answer << endl;
	return 0;
}