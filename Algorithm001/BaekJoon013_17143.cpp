#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int R, C, M, Answer = 0;

int catchManCol = 0;
int dx[5] = { 0, -1, 1, 0, 0 };
int dy[5] = { 0, 0, 0, 1, -1 };

int sharkIdxMap[102][102] = { 0, };

deque < pair<int, pair< pair<int, int>, pair<int, int>>>> shark;

void print_shark() {
	cout << "Map" << endl;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cout << sharkIdxMap[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;

	cout << shark.size()<< "마리 상어 정보" << endl;
	for (int i = 0; i < shark.size(); i++) {
		cout << i + 1 << "번 상어 크기 : " << shark[i].first << ", 위치: (" << shark[i].second.first.first << ", " << shark[i].second.first.second << "), 속력: " << shark[i].second.second.first << ", 방향" << shark[i].second.second.second << endl;
	}
}

void move_shark(int catchSharkIdx) {
	int startX, startY, curDir, curVel, nextX, nextY, nextDir, sharkSize, DequeSize;
	int change = 0, idx;

	//맵 초기화
	for (idx = 0; idx < shark.size(); idx++) {
		startX = shark[idx].second.first.first;
		startY = shark[idx].second.first.second;
		sharkIdxMap[startX][startY] = 0;
	}

	//상어별 시뮬레이션
	idx = 1;
	DequeSize = shark.size();
	for (int i = 1; i <= DequeSize; i++) {
		sharkSize = shark.front().first;
		startX = shark.front().second.first.first;
		startY = shark.front().second.first.second;
		curVel = shark.front().second.second.first;
		curDir = shark.front().second.second.second;
		shark.pop_front();

		//잡힌 상어면 pop만 진행 -> map 초기화 후 continue
		if (i == catchSharkIdx) {
			continue;
		}
		else if (curVel == 0) { 
			sharkIdxMap[startX][startY] = idx;
			shark.push_back(make_pair(sharkSize, make_pair(make_pair(startX, startY), make_pair(curVel, curDir))));
			idx++;
			continue;
		}

		change = 0;
		switch (curDir) {
		case 1:
			nextX = startX;
			nextY = startY;
			while (1) {
				nextDir = curDir;
				for (; change < curVel; change++) {
					nextX = nextX + dx[nextDir];
					if (nextX < 1) {
						nextX = 1;
						break;
					}
				}
				if (change == curVel) break;

				nextDir = curDir + 1;
				for (; change < curVel; change++) {
					nextX = nextX + dx[nextDir];
					if (nextX > R) {
						nextX = R;
						break;
					}
				}
				if (change == curVel) break;
			}			
			break;
		case 2:
			nextX = startX;
			nextY = startY;
			while (1) {
				nextDir = curDir;
				for (; change < curVel; change++) {
					nextX = nextX + dx[nextDir];
					if (nextX > R) {
						nextX = R;
						break;
					}
				}
				if (change == curVel) break;

				nextDir = curDir - 1;
				for (; change < curVel; change++) {
					nextX = nextX + dx[nextDir];
					if (nextX < 1) {
						nextX = 1;
						break;
					}
				}
				if (change == curVel) break;
			}
			break;
		case 3:
			nextX = startX;
			nextY = startY;
			while (1) {
				nextDir = curDir;
				for (; change < curVel; change++) {
					nextY = nextY + dy[nextDir];
					if (nextY > C) {
						nextY = C;
						break;
					}
				}
				if (change == curVel) break;

				nextDir = curDir + 1;
				for (; change < curVel; change++) {
					nextY = nextY + dy[nextDir];
					if (nextY < 1) {
						nextY = 1;
						break;
					}
				}
				if (change == curVel) break;
			}
			break;
		case 4:
			nextX = startX;
			nextY = startY;
			while (1) {
				nextDir = curDir;
				for (; change < curVel; change++) {
					nextY = nextY + dy[nextDir];
					if (nextY < 1) {
						nextY = 1;
						break;
					}
				}
				if (change == curVel) break;

				nextDir = curDir - 1;
				for (; change < curVel; change++) {
					nextY = nextY + dy[nextDir];
					if (nextY > C) {
						nextY = C;
						break;
					}
				}
				if (change == curVel) break;
			}
			break;
		}
		//다른 사이즈 큰 상어가 있다면 추가 X
		if (sharkIdxMap[nextX][nextY] == 0) {
			sharkIdxMap[nextX][nextY] = idx;
			shark.push_back(make_pair(sharkSize, make_pair(make_pair(nextX, nextY), make_pair(curVel, nextDir))));
			idx++;
		}
	}

	
}

int catch_shark(int startY) {
	int returnSharkIdx = 0;
	for (int row = 1; row <= R; row++) {
		if (sharkIdxMap[row][startY] != 0) {
			returnSharkIdx = sharkIdxMap[row][startY];
			Answer += shark[returnSharkIdx-1].first;
			break;
		}
	}
	return returnSharkIdx;
}

void Solve() {
	int catchSharkIdx = 0;
	Answer = 0;
	catchManCol = 0;

	while (1) {
		catchManCol++;
		catchSharkIdx = catch_shark(catchManCol);
		cout << endl;
		cout << catchManCol << "열에서 "<< catchSharkIdx << "번 상어 잡힘" << endl;
		move_shark(catchSharkIdx);
		print_shark();
		if (catchManCol == C) break;
	}
	/*
	catchManCol++;
	catchSharkIdx = catch_shark(catchManCol);
	cout << catchSharkIdx << "번 상어 잡힘" << endl;
	move_shark(catchSharkIdx);
	print_shark();


	catchManCol++;
	catchSharkIdx = catch_shark(catchManCol);
	cout << catchSharkIdx << "번 상어 잡힘" << endl;
	move_shark(catchSharkIdx);
	print_shark();
	*/
	
}

bool compare(pair<int, pair< pair<int, int>, pair<int, int>>> a, pair<int, pair< pair<int, int>, pair<int, int>>> b) {
	return a.first > b.first;
}

void Input() {
	int tmpX, tmpY, tmpS, tmpD, tmpZ;
	cin >> R >> C >> M;
	for (int i = 1; i <= M; i++) {
		cin >> tmpX >> tmpY >> tmpS >> tmpD >> tmpZ;
		shark.push_back(make_pair(tmpZ, make_pair(make_pair(tmpX, tmpY), make_pair(tmpS, tmpD))));
	}

	sort(shark.begin(), shark.end(), compare);

	for (int i = 0; i < shark.size(); i++) {
		tmpX = shark[i].second.first.first;
		tmpY = shark[i].second.first.second;
		sharkIdxMap[tmpX][tmpY] = i + 1;
	}
}


int main(void) {

	Input();
	print_shark();
	Solve();
	cout << Answer << endl;
	return 0;
}