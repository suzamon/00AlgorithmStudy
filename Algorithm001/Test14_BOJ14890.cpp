#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

#define MAX_N 101

using namespace std;

int N, L, Answer = 0;
int map[MAX_N][MAX_N], road[MAX_N][2];

int find_road() {
	int retFlag = 0, idx = 0, sIdx, tmpVal;

	for (idx = 0; idx < (N - 1); idx++) {
		if (road[idx][0] == road[idx + 1][0]) continue;
		else if (abs(road[idx][0] - road[idx + 1][0]) > 1) {
			return 1;
		}
		else if (road[idx][0] > road[idx + 1][0]) {
			if (idx + L > N) return 1;
			tmpVal = road[idx + 1][0];
			for (sIdx = idx + 1; sIdx <= (idx + L); sIdx++) {
				if (road[sIdx][0] == tmpVal && road[sIdx][1] == 0) {
					road[sIdx][1] = 1;
				}
				else return 1;
			}
			idx = idx + L - 1;
		}
		else if (road[idx][0] < road[idx + 1][0]) {
			if ((idx + 1) - L < 0) return 1;
			tmpVal = road[idx][0];
			for (sIdx = idx; sIdx >= (idx + 1 - L); sIdx--) {
				if (road[sIdx][0] == tmpVal && road[sIdx][1] == 0) {
					road[sIdx][1] = 1;
				}
				else return 1;
			}
		}
	}

	return 0;
}

void copy_arr(int idx, int dir) {
	int row, col;
	if (dir == 0) {
		row = idx;
		for (col = 0; col < N; col++) {
			road[col][0] = map[row][col];
			road[col][1] = 0;
		}
	}
	else {
		col = idx;
		for (row = 0; row < N; row++) {
			road[row][0] = map[row][col];
			road[row][1] = 0;
		}
	}

}
void Solution() {
	int flag = 0;
	for (int row = 0; row < N; row++) {
		copy_arr(row, 0);
		flag = find_road();
		if (flag == 0) {
			//cout << row << "번 행 가능" << endl;
			Answer++;
		}
	}
	for (int col = 0; col < N; col++) {
		copy_arr(col, 1);
		flag = find_road();
		if (flag == 0) {
			//cout << col << "번 열 가능" << endl;
			Answer++;
		}
	}

	cout << Answer << endl;

}

void Input() {
	cin >> N >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
}


int main(void) {
	Input();
	Solution();
	return 0;
}