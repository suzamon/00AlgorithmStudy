#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;

int N, K, L, Answer = 0;
int map[102][102];
int apple[101][2];
int dirArr[101][2];

//방향 0: 오른, 1:아래, 2:왼, 3 : 위
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int snakeHead[3] = { 1, 1, 0 }; //뱀 머리 x, y, 방향

void print_map() {
	cout << "Map" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
}

int change_dir(int curDir, int dirIndex) {
	int nextDir;
	if (dirArr[dirIndex][1] == 1) { //방향 왼쪽으로 방향 전환
		if (curDir > 0)  nextDir = curDir - 1;
		else nextDir = 3;
	}
	else { // 방향 오른쪽으로 방향 전환
		if (curDir < 3 )  nextDir = curDir + 1;
		else nextDir = 0;
	}

	return nextDir;
}

int move_simulation() {
	queue <pair <int, int>> snakePos;

	int time = 1, dirIndex = 0;
	int startX = snakeHead[0], startY = snakeHead[1], nextX, nextY, curDir, eraX, eraY;
	snakePos.push(make_pair(snakeHead[0], snakeHead[1]));
	
	while (1) {
		curDir = snakeHead[2];
		startX = snakeHead[0];
		startY = snakeHead[1];
		nextX = startX + dx[curDir];
		nextY = startY + dy[curDir];

		if (map[nextX][nextY] == 1) break;
		if (nextX == 0 || nextY == 0 || nextX == N + 1 || nextY == N + 1) break;

		if (map[nextX][nextY] == 2) {
			map[nextX][nextY] = 1;
			snakePos.push(make_pair(nextX, nextY));
			snakeHead[0] = nextX;
			snakeHead[1] = nextY;
		}
		else {
			map[nextX][nextY] = 1;
			snakePos.push(make_pair(nextX, nextY));
			snakeHead[0] = nextX;
			snakeHead[1] = nextY;

			eraX = snakePos.front().first;
			eraY = snakePos.front().second;
			snakePos.pop();
			map[eraX][eraY] = 0;

		}

		//cout << time << "초 후" << endl;
		//print_map();

		if (time == dirArr[dirIndex][0]) {
			snakeHead[2] = change_dir(snakeHead[2], dirIndex);
			dirIndex++;
		}
		time++;
	}

	return time;

}

void Input() {
	cin >> N >> K;
	for (int i = 0; i < K; i++) {
		cin >> apple[i][0] >> apple[i][1];
		map[apple[i][0]][apple[i][1]] = 2;
	}
	map[1][1] = 1;

	cin >> L;
	char temp;
	for (int i = 0; i < L; i++) {
		cin >> dirArr[i][0];
		cin >> temp;
		if (temp == 'L') {
			dirArr[i][1] = 1;
		}
		else {
			dirArr[i][1] = 2;
		}
	}
}

int main(void) {
	Input();
	//print_map();

	Answer = move_simulation();

	cout << Answer << endl;
	return 0;
}

