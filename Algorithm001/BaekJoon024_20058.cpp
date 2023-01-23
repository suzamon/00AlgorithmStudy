#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <deque>
#include <cmath>

using namespace std;

int N, Q, matrixSize, Answer1, Answer2;

int dx[4] = { -1, 1, 0, 0 }; //»óÇÏÁÂ¿ì
int dy[4] = { 0, 0, -1, 1 }; //»óÇÏÁÂ¿ì

int map[65][65];
int copyMap[65][65];
int visited[65][65];
int command[1001];

void print_map() {
	cout << "¸Ê Á¤º¸" << endl;
	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void find_dfs(int startX, int startY, int iceCnt) {
	int nextX, nextY;

	if (iceCnt > Answer2) Answer2 = iceCnt;

	for (int i = 0; i < 4; i++) {
		nextX = startX + dx[i];
		nextY = startY + dy[i];
		if (nextX >= 0 && nextX < matrixSize && nextY >= 0 && nextY < matrixSize && visited[nextX][nextY] == 0 && map[nextX][nextY] > 0) {
			visited[nextX][nextY] = 1;
			find_dfs(nextX, nextY, iceCnt + 1);
		}
	}
}

void find_bfs(int startX, int startY) {
	int iceCnt = 1, nextX, nextY;
	queue <pair<int,int>> q;
	q.push(make_pair(startX, startY));
	visited[startX][startY] = 1;

	while (!q.empty()) {
		startX = q.front().first;
		startY = q.front().second;
		q.pop();
		for(int i=0; i<4; i++){
			nextX = startX + dx[i];
			nextY = startY + dy[i];
			if (nextX >= 0 && nextX < matrixSize && nextY >= 0 && nextY < matrixSize && visited[nextX][nextY] == 0 && map[nextX][nextY] > 0) {
				visited[nextX][nextY] = 1;
				q.push(make_pair(nextX, nextY));
				iceCnt++;
			}
		}
	}

	if (iceCnt > Answer2) Answer2 = iceCnt;

}

void find_Answer() {
	Answer1 = 0;
	Answer2 = 0;
	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			Answer1 += map[i][j];
			if (visited[i][j] == 0 && map[i][j] > 0) {
				visited[i][j] = 1;
				find_bfs(i, j);
			}
		}
	}
}

void reduce_ice() {
	int startX, startY, nextX, nextY, emptyCnt;

	deque <pair<int, int>> reducePos;
	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			if (map[i][j] == 0) continue;
			emptyCnt = 0;
			startX = i;
			startY = j;
			for (int d = 0; d < 4; d++) {
				nextX = startX + dx[d];
				nextY = startY + dy[d];
				if (!(nextX >= 0 && nextX < matrixSize && nextY >= 0 && nextY < matrixSize && map[nextX][nextY]>0)) {
					emptyCnt++;
				}
				if (emptyCnt >= 2) {
					reducePos.push_back(make_pair(startX, startY));
					break;
				}
			}
		}
	}
	while (!reducePos.empty()) {
		startX = reducePos.front().first;
		startY = reducePos.front().second;
		map[startX][startY]--;
		reducePos.pop_front();
	}
}

void rot_map(int rowStart, int rowEnd, int colStart, int colEnd) {
	int subMatrixSize = rowEnd - rowStart;

	for (int i = rowStart; i < rowEnd; i++) {
		for (int j = colStart; j < colEnd; j++) {
			copyMap[i - rowStart][j - colStart] = map[i][j];
		}
	}

	for (int i = rowStart; i < rowEnd; i++) {
		for (int j = colStart; j < colEnd; j++) {
			map[rowStart + (j-colStart)][colStart + subMatrixSize - 1 - (i-rowStart)] = copyMap[i - rowStart][j - colStart];
		}
	}

}

void Solution() {
	int curCommand, divideSize;
	for (int i = 0; i < Q; i++) {
		curCommand = command[i];
		divideSize = pow(2, curCommand);

		for (int row = 0; row < matrixSize; row += divideSize) {
			for (int col = 0; col < matrixSize; col += divideSize) {
				rot_map(row, row + divideSize, col, col + divideSize);
			}
		}
		reduce_ice();
	}

	find_Answer();

}

void Input() {
	cin >> N >> Q;

	matrixSize = pow(2, N);
	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < Q; i++) {
		cin >> command[i];
	}
}

int main(void) {

	Input();
	Solution();
	cout << Answer1 << endl;
	cout << Answer2 << endl;
	return 0;
}