#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int minRow = 100, minCol = 100, maxRow = 0, maxCol = 0, N, Answer = 0;

int map[101][101] = { 0, };
int dragon[21][4] = { 0, };

int dx[4] = { 0, -1, 0, 1 };
int dy[4] = { 1, 0, -1, 0 };

int checkDx[3] = { 0, 1, 1 };
int checkDy[3] = { 1, 0, 1 };

void print_info() {
	cout << "¸Ê Á¤º¸" << endl;
	for (int i = 0; i <= 6; i++) {
		for (int j = 0; j <= 6; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void update_map(int xx, int yy) {
	if (xx < minRow) minRow = xx;
	if (xx > maxRow) maxRow = xx;
	if (yy < minCol) minCol = yy;
	if (yy > maxCol) maxCol = yy;
}

int rotate_curve(int dir) {
	int nD = dir + 1;
	if (nD == 4) nD = 0;
	return nD;
}

bool inRange(int xx, int yy) {
	if (xx >= 0 && xx < 101 && yy >= 0 && yy < 101) return true;
	return false;
}

void findDragonCurve(int idx) {
	deque <int> dq;
	int dqSize, d, g, nD;

	d = dragon[idx][2], g = dragon[idx][3];

	dq.push_back(d);

	for (int i = 0; i < g; i++) {
		dqSize = dq.size();
		for (int j = dqSize - 1; j >= 0; j--) {
			nD = rotate_curve(dq[j]);
			dq.push_back(nD);
		}
	}

	int sX = dragon[idx][0], sY = dragon[idx][1], dir;
	map[sX][sY] = 1;
	update_map(sX, sY);
	while (!dq.empty()) {
		dir = dq.front();
		dq.pop_front();
		sX = sX + dx[dir], sY = sY + dy[dir];
		if (!inRange(sX, sY)) continue;
		update_map(sX, sY);
		map[sX][sY] = 1;
	}
	
}

void find_answer() {
	int row, col, xx, yy, flag;

	for (row = minRow; row <= maxRow; row++) {
		for (col = minCol; col <= maxCol; col++) {
			if(row + 1 > 100 || col + 1 > 100) continue;
			xx = row, yy = col;
			if (map[xx][yy] > 0) {
				flag = 0;
				for (int dir = 0; dir < 4; dir++) {
					xx = row + checkDx[dir], yy = col + checkDy[dir];
					if (map[xx][yy] == 0) {
						flag = 1;
						break;
					}
				}
				if (flag == 0) Answer++;
			}
		}
	}
}

void Solution() {
	for (int i = 0; i < N; i++) {
		findDragonCurve(i);
		//print_info();
	}

	//print_info();
	find_answer();
	cout << Answer << endl;

}

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> dragon[i][1] >> dragon[i][0];
		for (int j = 2; j < 4; j++) {
			cin >> dragon[i][j];
		}
	}

}


int main(void) {
	Input();
	Solution();
	return 0;
}