#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <deque>
#include <cmath>

using namespace std;

int N, M, Answer = 0;
int map[50][50];
int command[101][2];

int dx[5] = { 0, -1, 1, 0, 0 };
int dy[5] = { 0, 0, 0, -1, 1 };

int sharkPos[2];

int removeBall[4] = { 0, };

void print_map() {
	cout << "¸Ê Á¤º¸" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void find_answer() {
	Answer = 0;
	for (int i = 1; i <= 3; i++) {
		Answer += (i * removeBall[i]);
	}
}

void union_ball() {
	int startX, startY, beforeValue, ballNum, ballCnt;
	int retFlag = 1;
	int extFlag = 0;
	int moveDx[5] = { 0, 0, 1, 0, -1 };
	int moveDy[5] = { 0, -1, 0, 1, 0 };

	queue <pair<int, int>> q;

	startX = sharkPos[0];
	startY = sharkPos[1];


	int size = 0;
	beforeValue = -1;
	ballCnt = 0;
	while (1) {
		size++;
		for (int i = 1; i < 3; i++) {
			for (int s = 0; s < size; s++) {
				startX = startX + moveDx[i];
				startY = startY + moveDy[i];
				if (beforeValue == -1) {
					beforeValue = map[startX][startY];
					ballCnt = 1;
					map[startX][startY] = 0;
				}
				else if (map[startX][startY] == beforeValue) {
					ballCnt++;
					map[startX][startY] = 0;
				}
				else if (map[startX][startY] == 0) {
					q.push(make_pair(beforeValue, ballCnt));
					extFlag = 1;
					break;
				}
				else {
					q.push(make_pair(beforeValue, ballCnt));
					beforeValue = map[startX][startY];
					ballCnt = 1;
					map[startX][startY] = 0;
				}

				if (startX == 1 && startY == 1) {
					q.push(make_pair(beforeValue, ballCnt));
					map[startX][startY] = 0;
					extFlag = 1;
					break;
				}

				if ((2 * q.size()) >= ((N*N) - 1)) {
					extFlag = 1;
					break;
				}
			}
			if (extFlag == 1) break;
		}
		if (extFlag == 1) break;

		size++;
		for (int i = 3; i < 5; i++) {
			for (int s = 0; s < size; s++) {
				startX = startX + moveDx[i];
				startY = startY + moveDy[i];
				if (map[startX][startY] == beforeValue) {
					ballCnt++;
					map[startX][startY] = 0;
				}
				else if (map[startX][startY] == 0) {
					q.push(make_pair(beforeValue, ballCnt));
					extFlag = 1;
					break;
				}
				else {
					q.push(make_pair(beforeValue, ballCnt));
					beforeValue = map[startX][startY];
					ballCnt = 1;
					map[startX][startY] = 0;
				}
				if ((2 * q.size()) >= ((N*N) - 1)) {
					extFlag = 1;
					break;
				}
			}
			if (extFlag == 1) break;
		}
		if (extFlag == 1) break;
	}

	size = 0;
	if (q.size() == 0) return;


	startX = sharkPos[0];
	startY = sharkPos[1];
	ballCnt = 0, ballNum = 0;
	while (1) {
		size++;
		for (int i = 1; i < 3; i++) {
			for (int s = 0; s < size; s++) {
				startX = startX + moveDx[i];
				startY = startY + moveDy[i];
				if(ballCnt == 0 && ballNum != 0){
					map[startX][startY] = ballNum;
					ballNum = 0;
				}
				else {
					if (q.size() == 0) break;
					ballCnt = q.front().second;
					ballNum = q.front().first;
					q.pop();
					map[startX][startY] = ballCnt;
					ballCnt = 0;
				}

				if (startX == 1 && startY == 1) {
					while (!q.empty()) {
						q.pop();
					}
					break;
				}
			}
			if (startX == 1 && startY == 1) break;
			if (q.size() == 0) break;
		}
		if (startX == 1 && startY == 1) break;
		if (q.size() == 0) break;

		size++;
		for (int i = 3; i < 5; i++) {
			for (int s = 0; s < size; s++) {
				startX = startX + moveDx[i];
				startY = startY + moveDy[i];
				if (ballCnt == 0 && ballNum != 0) {
					map[startX][startY] = ballNum;
					ballNum = 0;
				}
				else {
					if (q.size() == 0) break;
					ballCnt = q.front().second;
					ballNum = q.front().first;
					q.pop();
					map[startX][startY] = ballCnt;
					ballCnt = 0;
				}
			}
			if (q.size() == 0) break;
		}
		if (q.size() == 0) break;
	}

}

int remove_ball() {
	int startX, startY, rX, rY;
	int retFlag = 0;
	int moveDx[5] = { 0, 0, 1, 0, -1 };
	int moveDy[5] = { 0, -1, 0, 1, 0 };

	queue <pair <int, int>> removePos;
	int beforeValue = -1;

	startX = sharkPos[0];
	startY = sharkPos[1];

	int size = 0;
	while (1) {
		size++;
		for (int i = 1; i < 3; i++) {
			for (int s = 0; s < size; s++) {
				startX = startX + moveDx[i];
				startY = startY + moveDy[i];
				if (beforeValue == -1) {
					beforeValue = map[startX][startY];
					removePos.push(make_pair(startX, startY));
				}
				else if (map[startX][startY] == beforeValue) {
					removePos.push(make_pair(startX, startY));
				}
				else {
					if (removePos.size() >= 4) {
						removeBall[beforeValue] += removePos.size();
						while (!removePos.empty()) {
							rX = removePos.front().first;
							rY = removePos.front().second;
							removePos.pop();
							map[rX][rY] = 0;
						}
						retFlag = 1;

					}
					else {
						while (!removePos.empty()) {
							removePos.pop();
						}
					}
					beforeValue = map[startX][startY];
					removePos.push(make_pair(startX, startY));
				}

				if (startX == 1 && startY == 1) {
					if (removePos.size() >= 4) {
						removeBall[beforeValue] += removePos.size();
						while (!removePos.empty()) {
							rX = removePos.front().first;
							rY = removePos.front().second;
							removePos.pop();
							map[rX][rY] = 0;
						}
						retFlag = 1;
					}
					else {
						while (!removePos.empty()) {
							removePos.pop();
						}
					}
					break;
				}

				if (map[startX][startY] == 0) {
					if (removePos.size() >= 4) {
						removeBall[beforeValue] += removePos.size();
						while (!removePos.empty()) {
							rX = removePos.front().first;
							rY = removePos.front().second;
							removePos.pop();
							map[rX][rY] = 0;
						}
						retFlag = 1;
					}
					else {
						while (!removePos.empty()) {
							removePos.pop();
						}
					}
					break;
				}
			}
			if (startX == 1 && startY == 1) break;
			if (map[startX][startY] == 0) break;
		}
		if (startX == 1 && startY == 1) break;
		if (map[startX][startY] == 0) break;

		size++;
		for (int i = 3; i < 5; i++) {
			for (int s = 0; s < size; s++) {
				startX = startX + moveDx[i];
				startY = startY + moveDy[i];

				if (map[startX][startY] == beforeValue) {
					removePos.push(make_pair(startX, startY));
				}
				else {
					if (removePos.size() >= 4) {
						removeBall[beforeValue] += removePos.size();
						while (!removePos.empty()) {
							rX = removePos.front().first;
							rY = removePos.front().second;
							removePos.pop();
							map[rX][rY] = 0;
						}
						retFlag = 1;
					}
					else {
						while (!removePos.empty()) {
							removePos.pop();
						}
					}
					beforeValue = map[startX][startY];
					removePos.push(make_pair(startX, startY));
				}

				if (map[startX][startY] == 0) {
					if (removePos.size() >= 4) {
						removeBall[beforeValue] += removePos.size();
						while (!removePos.empty()) {
							rX = removePos.front().first;
							rY = removePos.front().second;
							removePos.pop();
							map[rX][rY] = 0;
						}
						retFlag = 1;
					}
					else {
						while (!removePos.empty()) {
							removePos.pop();
						}
					}
					break;
				}

			}
			if (map[startX][startY] == 0) break;
		}
		if (map[startX][startY] == 0) break;
	}

	return retFlag;
}

int move_ball() {
	int startX, startY;
	int retFlag = 1;
	int moveDx[5] = { 0, 0, 1, 0, -1 };
	int moveDy[5] = { 0, -1, 0, 1, 0 };

	queue <int> q;

	startX = sharkPos[0];
	startY = sharkPos[1];


	int size = 0;
	while (1) {
		size++;
		for (int i = 1; i < 3; i++) {
			for (int s = 0; s < size; s++) {
				startX = startX + moveDx[i];
				startY = startY + moveDy[i];
				if (startX == 1 && startY == 1) {
					if (map[startX][startY] != 0) {
						q.push(map[startX][startY]);
						map[startX][startY] = 0;
					}
					break;
				}
				if (map[startX][startY] != 0) {
					q.push(map[startX][startY]);
					map[startX][startY] = 0;
				}
			}
			if (startX == 1 && startY == 1) break;
		}
		if (startX == 1 && startY == 1) break;

		size++;
		for (int i = 3; i < 5; i++) {
			for (int s = 0; s < size; s++) {
				startX = startX + moveDx[i];
				startY = startY + moveDy[i];
				if (map[startX][startY] != 0) {
					q.push(map[startX][startY]);
					map[startX][startY] = 0;
				}
			}
		}
	}

	int tmp;
	startX = sharkPos[0];
	startY = sharkPos[1];

	if (q.size() == 0) {
		retFlag = 0;
		return retFlag;
	}

	size = 0;
	while (!q.empty()) {
		size++;
		for (int i = 1; i < 3; i++) {
			for (int s = 0; s < size; s++) {
				startX = startX + moveDx[i];
				startY = startY + moveDy[i];

				tmp = q.front();
				q.pop();

				if (startX == 1 && startY == 1) {
					map[startX][startY] = tmp;
					break;
				}
				map[startX][startY] = tmp;
				if (q.size() == 0) break;
			}
			if (q.size() == 0) break;
			if (startX == 1 && startY == 1) break;
		}
		if (q.size() == 0) break;
		if (startX == 1 && startY == 1) break;

		size++;
		for (int i = 3; i < 5; i++) {
			for (int s = 0; s < size; s++) {
				startX = startX + moveDx[i];
				startY = startY + moveDy[i];

				tmp = q.front();
				q.pop();

				map[startX][startY] = tmp;
				if (q.size() == 0) break;
			}
			if (q.size() == 0) break;
		}
		if (q.size() == 0) break;
	}

	return retFlag;
}

void shark_magic(int d, int s) {
	int startX, startY, nextX, nextY;

	startX = sharkPos[0];
	startY = sharkPos[1];

	for (int i = 0; i < s ; i++) {
		nextX = startX + dx[d];
		nextY = startY + dy[d];
		map[nextX][nextY] = 0;

		startX = nextX;
		startY = nextY;
	}


}

void Solution() {
	int extFlag = 0;

	for (int time = 1; time <= M; time++) {
		extFlag = 1;
		shark_magic(command[time][0], command[time][1]);
		extFlag = move_ball();
		if(extFlag == 0) break;
		while(1){
			extFlag = remove_ball();
			if(extFlag == 0) break;
			move_ball();
		}
		union_ball();
		//print_map();
	}
	
	find_answer();
}

void Input() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}

	sharkPos[0] = (N + 1) / 2;
	sharkPos[1] = (N + 1) / 2;

	for (int i = 1; i <= M; i++) {
		cin >> command[i][0] >> command[i][1];
	}
}

int main(void) {
	Input();
	Solution();

	cout << Answer << endl;
	return 0;
}