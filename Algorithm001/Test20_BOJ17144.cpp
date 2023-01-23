#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int R, C, T, Answer = 0;
int map[51][51], airCond[2];

deque <pair <int, pair <int, int>>> dust;
deque <pair <int, pair <int, int>>> addDust;

int dx[5] = { 0, 1, 0, -1, 0 };
int dy[5] = { 0, 0, 1, 0, -1 };

bool inRange(int xx, int yy) {
	if (xx > 0 && xx <= R && yy > 0 && yy <= C) return true;
	return false;
}

void print_info() {
	cout << "¸Ê Á¤º¸" << endl;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
}

void spread_dust() {
	int sX, sY, sDust, nX, nY, nDust, d, dustSize, tmpCnt;

	dustSize = dust.size();
	for (int i = 0; i < dustSize; i++) {
		sDust = dust.front().first;
		sX = dust.front().second.first, sY = dust.front().second.second;
		dust.pop_front();
		if (sDust < 5) continue;

		tmpCnt = 0;
		nDust = sDust / 5;
		for (d = 1; d <= 4; d++) {
			nX = sX + dx[d], nY = sY + dy[d];
			if (!inRange(nX, nY) || map[nX][nY] == -1) continue;

			tmpCnt++;
			addDust.push_back(make_pair(nDust, make_pair(nX, nY)));
		}

		sDust = sDust - (nDust * tmpCnt);
		map[sX][sY] = sDust;
	}

	while (!addDust.empty()) {
		sDust = addDust.front().first;
		sX = addDust.front().second.first, sY = addDust.front().second.second;
		addDust.pop_front();
		map[sX][sY] = map[sX][sY] + sDust;
	}

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (map[i][j] > 0) dust.push_back(make_pair(map[i][j], make_pair(i, j)));
		}
	}
}

bool check_dust(int row, int col) {
	if (row == 1 || row == airCond[0] || row == airCond[1] || row == R) return true;
	else if (col == 1 || col == C) return true;

	return false;
}

void circulate_air() {
	int sX, sY, sDust, nX, nY, dustSize;

	dustSize = dust.size();
	for (int i = 0; i < dustSize; i++) {
		sDust = dust.front().first;
		sX = dust.front().second.first, sY = dust.front().second.second;
		dust.pop_front();

		if (!check_dust(sX, sY)) {
			dust.push_back(make_pair(sDust, make_pair(sX, sY)));
			continue;
		}

		if (sX == airCond[0]) {
			map[sX][sY] = 0;
			if (sY == C) {
				dust.push_back(make_pair(sDust, make_pair(sX - 1, sY)));
			}
			else {
				dust.push_back(make_pair(sDust, make_pair(sX, sY + 1)));
			}
		}
		else if (sX == 1) {
			map[sX][sY] = 0;
			if (sY == 1) {
				dust.push_back(make_pair(sDust, make_pair(sX + 1, sY)));
			}
			else {
				dust.push_back(make_pair(sDust, make_pair(sX, sY - 1)));
			}
		}
		else if (sX == airCond[1]) {
			map[sX][sY] = 0;
			if (sY == C) {
				dust.push_back(make_pair(sDust, make_pair(sX + 1, sY)));
			}
			else {
				dust.push_back(make_pair(sDust, make_pair(sX, sY + 1)));
			}
		}
		else if (sX == R) {
			map[sX][sY] = 0;
			if (sY == 1) {
				dust.push_back(make_pair(sDust, make_pair(sX - 1, sY)));
			}
			else {
				dust.push_back(make_pair(sDust, make_pair(sX, sY - 1)));
			}
		}
		else if (sY == C) {
			map[sX][sY] = 0;
			if (sX < airCond[0]) {
				dust.push_back(make_pair(sDust, make_pair(sX - 1, sY)));
			}
			else if (sX > airCond[1]) {
				dust.push_back(make_pair(sDust, make_pair(sX + 1, sY)));
			}
		}
		else if(sY == 1){
			map[sX][sY] = 0;
			if (sX == (airCond[0] - 1) || sX == (airCond[1] + 1)) continue;
			else if (sX < airCond[0]) {
				dust.push_back(make_pair(sDust, make_pair(sX + 1, sY)));
			}
			else if (sX > airCond[1]) {
				dust.push_back(make_pair(sDust, make_pair(sX - 1, sY)));
			}
		}

	}


	dustSize = dust.size();
	for (int i = 0; i < dustSize; i++) {
		sDust = dust.front().first;
		sX = dust.front().second.first, sY = dust.front().second.second;
		dust.pop_front();
		map[sX][sY] = sDust;
		dust.push_back(make_pair(sDust, make_pair(sX, sY)));
	}
}

void find_answer() {
	int sDust, cnt = 0;
	Answer = 0;
	
	while (!dust.empty()) {
		sDust = dust.front().first;
		dust.pop_front();
		Answer = Answer + sDust;
	}
}

void Solution() {
	int time;

	for (time = 1; time <= T; time++) {
		spread_dust();
		circulate_air();
	}

	find_answer();
	cout << Answer << endl;
}

void Input() {
	int tmpIdx = 0;
	cin >> R >> C >> T;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> map[i][j];
			if (map[i][j] == -1) {
				airCond[tmpIdx] = i;
				tmpIdx++;
			}
			else if (map[i][j] > 0) {
				dust.push_back(make_pair(map[i][j], make_pair(i, j)));
			}
		}
	}
}


int main(void) {
	Input();
	Solution();
	return 0;
}