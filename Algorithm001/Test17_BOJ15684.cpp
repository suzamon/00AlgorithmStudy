#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, H, M, Answer = 0;
int map[31][11] = { 0, };

int Simulation() {
	int startRow, startCol, nextCol;

	for (startCol = 1; startCol <= N; startCol++) {
		nextCol = startCol;
		for (startRow = 1; startRow <= H; startRow++) {
			if (nextCol == 1) {
				if (map[startRow][nextCol] == 1) nextCol++;
			}
			else if (nextCol == N) {
				if (map[startRow][nextCol - 1] == 1) nextCol--;
			}
			else {
				if (map[startRow][nextCol] == 1) nextCol++;
				else if (map[startRow][nextCol - 1] == 1) nextCol--;
			}
		}
		//cout << startCol << ": " << nextCol << endl;
		if (nextCol != startCol) return -1;
	}

	return 1;
}

void add_labber(int startRow, int startCol, int cnt, int goal) {
	if (cnt == goal) {
		int retFlag = Simulation();
		if (retFlag == 1) {
			if (Answer == 0) Answer = goal;
			else if (Answer > goal) Answer = goal;
		}
		return;
	}

	if (startCol < N + 1) {
		for (; startCol <= N; startCol++) {
			if (Answer != 0) return;

			if (map[startRow][startCol] == 0) {
				if (startCol == 1) {
					if (map[startRow][startCol + 1] == 0) {
						map[startRow][startCol] = 1;
						add_labber(startRow, startCol + 1, cnt + 1, goal);
						map[startRow][startCol] = 0;
					}
				}
				else if (startCol == N) {
					if (map[startRow][startCol - 1] == 0) {
						map[startRow][startCol] = 1;
						add_labber(startRow, startCol + 1, cnt + 1, goal);
						map[startRow][startCol] = 0;
					}
				}
				else {
					if (map[startRow][startCol + 1] == 0 && map[startRow][startCol - 1] == 0) {
						map[startRow][startCol] = 1;
						add_labber(startRow, startCol + 1, cnt + 1, goal);
						map[startRow][startCol] = 0;
					}
				}
			}
		}
	}

	startRow = startRow + 1;
	for (; startRow <= H; startRow++) {
		if (Answer != 0) return;

		for (startCol = 1; startCol <= N; startCol++) {
			if (map[startRow][startCol] == 0) {
				if (startCol == 1) {
					if (map[startRow][startCol + 1] == 0) {
						map[startRow][startCol] = 1;
						add_labber(startRow, startCol + 1, cnt + 1, goal);
						map[startRow][startCol] = 0;
					}
				}
				else if (startCol == N) {
					if (map[startRow][startCol - 1] == 0) {
						map[startRow][startCol] = 1;
						add_labber(startRow, startCol + 1, cnt + 1, goal);
						map[startRow][startCol] = 0;
					}
				}
				else {
					if (map[startRow][startCol + 1] == 0 && map[startRow][startCol - 1] == 0) {
						map[startRow][startCol] = 1;
						add_labber(startRow, startCol + 1, cnt + 1, goal);
						map[startRow][startCol] = 0;
					}
				}
			}
		}
	}

}

void Solution() {
	int flag = 0, goal;
	flag = Simulation();
	if (flag == 1) return;

	for (goal = 1; goal <= 3; goal++) {
		add_labber(1, 1, 0, goal);
		if (Answer != 0) break;
	}

	if (Answer == 0 && goal == 4) Answer = -1;
}

void Input() {
	cin >> N >> M >> H;

	int xx, yy;
	for (int i = 0; i < M; i++) {
		cin >> xx >> yy;

		map[xx][yy] = 1;
	}

}


int main(void) {
	Input();
	//cout << Simulation() << endl;
	Solution();

	cout << Answer << endl;
	return 0;
}