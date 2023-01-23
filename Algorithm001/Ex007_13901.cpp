#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int R, C, K;
int map[1001][1001] = { 0, }, visited[1001][1001] = { 0, };
int startPos[2], endPos[2];

int dx[5] = { 0, -1, 1, 0, 0 };
int dy[5] = { 0, 0, 0, -1, 1 };

int dirCommand[4] = { 0, };

void Solution() {
	int startX, startY, nextX, nextY, curDir, nextDir, exitFlag;

	startX = startPos[0];
	startY = startPos[1];
	visited[startX][startY] = 1;
	curDir = 0;
	exitFlag = 0;
	//cout << '(' << startX << ", " << startY << ") 이동, 방향: " << dirCommand[curDir] << endl;
	while (1) {
		for (int i = 0; i < 4; i++) {
			if (i == 0) nextDir = curDir;
			else {
				nextDir++;
				nextDir = nextDir %4
			}

			nextX = startX + dx[dirCommand[nextDir]];
			nextY = startY + dy[dirCommand[nextDir]];

			if (nextX < 0 || nextX >= R || nextY < 0 || nextY >= C) continue;
			
			if (map[nextX][nextY] == 0 && visited[nextX][nextY] == 0) {
				visited[nextX][nextY] = 1;
				startX = nextX;
				startY = nextY;
				curDir = nextDir;
				//cout << '(' << startX << ", " << startY << ") 이동, 방향: " << nextDir << endl;
				break;
			}

			if (i == 3) exitFlag = 1;
		}
		if (exitFlag == 1) {
			endPos[0] = startX;
			endPos[1] = startY;
			break;
		}
	}


}

void Input() {
	int br, bc;
	cin >> R >> C >> K;
	for (int i = 0; i < K; i++) {
		cin >> br >> bc;
		map[br][bc] = 1;
	}
	cin >> startPos[0] >> startPos[1];

	for (int i = 0; i < 4; i++) {
		cin >> dirCommand[i];
	}

}

int main(void) {
	Input();
	Solution();
	cout << endPos[0] << ' ' << endPos[1] << endl;

	return 0;
}