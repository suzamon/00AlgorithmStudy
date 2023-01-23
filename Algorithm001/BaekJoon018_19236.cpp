#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

int N, Answer = 0;

int shark[4];
int fish[17][4];
int map[4][4];

int dx[9] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[9] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };

int nextSharkPos[4][2];

void print_map() {
	cout << "바닷가 맵" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;

	cout << "1. 물고기 정보" << endl;
	for (int i = 1; i <= 16; i++) {
		if (fish[i][3] == 1) {
			cout << i << "번 물고기 죽음" << endl;
			continue;
		}
		cout << i << "번 물고기 위치: " << fish[i][0] << ", " << fish[i][1] << ", 방향: " << fish[i][2] << endl;
	}
	cout << endl;

}

int find_shark_pos(int curX, int curY, int curDir) {
	int cnt = 0, nextX, nextY;

	for (int i = 1; i < 4; i++) {
		nextX = curX + i * dx[curDir];
		nextY = curY + i * dy[curDir];
		if (nextX >= 0 && nextX < 4 && nextY >= 0 && nextY < 4 && map[nextX][nextY] > 0) {
			nextSharkPos[cnt][0] = nextX;
			nextSharkPos[cnt][1] = nextY;
			cnt++;
		}
	}

	return cnt;
}

void sim_shark(int sharkX, int sharkY, int sharkDir, int sumFish, int flag) {
	if (sharkX == -1 && sharkY == -1) {
		if (sumFish > Answer) Answer = sumFish;
		return;
	}

	//1. 물고기 이동
	int fishNum, curX, curY, curDir, nextX, nextY, nextDir, changeFishNum;
	for (fishNum = 1; fishNum <= 16; fishNum++){
		if (fish[fishNum][3] == 1) {
			continue;

		}

		curX = fish[fishNum][0];
		curY = fish[fishNum][1];
		curDir = fish[fishNum][2];

		nextX = curX + dx[curDir];
		nextY = curY + dy[curDir];

		if (nextX >= 0 && nextX < 4 && nextY >= 0 && nextY < 4 && map[nextX][nextY] > -1) {
			if (map[nextX][nextY] == 0) {
				map[nextX][nextY] = fishNum;
				map[curX][curY] = 0;

				fish[fishNum][0] = nextX;
				fish[fishNum][1] = nextY;
			}
			else {
				changeFishNum = map[nextX][nextY];

				map[nextX][nextY] = fishNum;
				map[curX][curY] = changeFishNum;

				fish[fishNum][0] = nextX;
				fish[fishNum][1] = nextY;

				fish[changeFishNum][0] = curX;
				fish[changeFishNum][1] = curY;
			}

		}
		else {
			nextDir = curDir;
			for (int i = 0; i < 8; i++) {
				nextDir += 1;
				if (nextDir > 8) nextDir = 1;

				if (nextDir == curDir) break;

				nextX = curX + dx[nextDir];
				nextY = curY + dy[nextDir];

				if (nextX >= 0 && nextX < 4 && nextY >= 0 && nextY < 4 && map[nextX][nextY] > -1) {
					if (map[nextX][nextY] == 0) {
						map[nextX][nextY] = fishNum;
						map[curX][curY] = 0;

						fish[fishNum][0] = nextX;
						fish[fishNum][1] = nextY;
						fish[fishNum][2] = nextDir;
					}
					else {
						changeFishNum = map[nextX][nextY];

						map[nextX][nextY] = fishNum;
						map[curX][curY] = changeFishNum;

						fish[fishNum][0] = nextX;
						fish[fishNum][1] = nextY;
						fish[fishNum][2] = nextDir;

						fish[changeFishNum][0] = curX;
						fish[changeFishNum][1] = curY;
					}

					break;
				}

			}
		}
	}

	/*
	cout << flag << "번 상어 이동" << endl;
	cout << "상어 위치: (" << sharkX << ", " << sharkY << "), 방향: " << sharkDir << ", 상어가 먹은 물고기: " << sumFish << endl;
	print_map();
	*/
	//2. 상어 이동
	//2-1. 상어가 이동할 수 있는 위치 찾기
 	int repeatCnt = find_shark_pos(sharkX, sharkY, sharkDir);

	//2-2 상어 이동
	int nextSharkX, nextSharkY, nextSharkDir, eatFish, nextSumFish;
	int copy_fish[17][4];
	int copy_map[4][4];
	int copy_nextSharkPos[4][2];

	if (repeatCnt == 0) {
		sim_shark(-1, -1, -1, sumFish, flag);
	}
	else {
		
		//백업 데이터 저장
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				copy_map[i][j] = map[i][j];
			}
		}
		for (int i = 1; i <= 16; i++) {
			for (int j = 0; j < 4; j++) {
				copy_fish[i][j] = fish[i][j];
			}
		}
		if (repeatCnt > 1) {
			for (int i = 0; i < repeatCnt; i++) {
				for (int j = 0; j < 2; j++) {
					copy_nextSharkPos[i][j] = nextSharkPos[i][j];
				}
			}
		}
		
		for (int i = 0; i < repeatCnt; i++) {
			nextSharkX = nextSharkPos[i][0];
			nextSharkY = nextSharkPos[i][1];
			eatFish = map[nextSharkX][nextSharkY];
			nextSharkDir = fish[eatFish][2];
			nextSumFish = sumFish + eatFish;

			//맵과 물고기 정보 업데이트
			map[sharkX][sharkY] = 0;
			map[nextSharkX][nextSharkY] = -1;
			fish[eatFish][3] = 1;

			sim_shark(nextSharkX, nextSharkY, nextSharkDir, nextSumFish, flag + 1);

			//맵과 물고기 정보 복구
			/*
			map[sharkX][sharkY] = -1;
			map[nextSharkX][nextSharkY] = eatFish;
			fish[eatFish][3] = 0;
			*/
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					map[i][j] = copy_map[i][j];
				}
			}
			for (int i = 1; i <= 16; i++) {
				for (int j = 0; j < 4; j++) {
					fish[i][j] = copy_fish[i][j];
				}
			}
			if (repeatCnt > 1) {
				for (int j = i + 1; j < repeatCnt; j++) {
					for (int k = 0; k < 2; k++) {
						nextSharkPos[j][k] = copy_nextSharkPos[j][k];
					}
				}
			}
		}


	}
	
}

void Solve() {
	int fishNum, fishDir;
	
	//1. 상어 0,0으로 이동
	shark[0] = 0;
	shark[1] = 0;

	fishNum = map[shark[0]][shark[1]];
	map[shark[0]][shark[1]] = -1;

	shark[2] = fish[fishNum][2];
	fish[fishNum][3] = 1;
	shark[3] = fishNum;

	sim_shark(shark[0], shark[1], shark[2], shark[3], 1);
}

void Input() {
	int fishNum, fishDir;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> fishNum >> fishDir;

			map[i][j] = fishNum;

			fish[fishNum][0] = i;
			fish[fishNum][1] = j;
			fish[fishNum][2] = fishDir;
			fish[fishNum][3] = 0;
		}
	}
	//print_map();
}

int main(void) {
	Input();
	Solve();

	cout << Answer << endl;

	return 0;
}