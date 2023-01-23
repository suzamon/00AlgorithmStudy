#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>
#include <cmath>

using namespace std;

int N, K, Answer = -1;
int map[13][13];
int exitFlag = 0;

deque <pair<pair<int, int>, int>> chess; //체스말 정보 -> x, y, dir
deque <int> chessMap[13][13]; //체스말 맵 정보

int dx[5] = { 0, 0, 0, -1, 1 };
int dy[5] = { 0, 1, -1, 0, 0 };

void print() {
	cout << "Map" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;

	cout << "체스말 정보" << endl;
	for (int chessIdx = 0; chessIdx < K; chessIdx++) {
		cout << chessIdx +1 << "번 체스말 위치: (" << chess[chessIdx].first.first << ", " << chess[chessIdx].first.second << "), 방향: " << chess[chessIdx].second << endl;
	}
	cout << endl;

	cout << "체스말 맵 정보" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (chessMap[i][j].size() >= 1) {
				cout << "(" << i << ", " << j << "), 위치에 ";
				for (int k = 0; k < chessMap[i][j].size(); k++) {
					cout << chessMap[i][j][k] + 1 << ", ";
				}
				cout << "순서대로 체스말 존재" << endl;
			}
		}
	}
	cout << endl;
}

int find_exit() {
	int flag = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (chessMap[i][j].size() >= 4) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) break;
	}
	return flag;
}

void move_chess(int chessIdx, int startX, int startY, int curDir) {
	queue <int> stay;
	deque <int> move;

	int nextX, nextY, nextDir, tmpIdx;

	if (chessMap[startX][startY].size() == 1) {
		chessMap[startX][startY].pop_front();
		nextX = startX + dx[curDir];
		nextY = startY + dy[curDir];
		if (nextX < 1 || nextX > N || nextY < 1 || nextY > N || map[nextX][nextY] == 2) {
			if (curDir == 2 || curDir == 4) nextDir = curDir-1;
			else nextDir = curDir+1;

			nextX = startX + dx[nextDir];
			nextY = startY + dy[nextDir];
			if (nextX < 1 || nextX > N || nextY < 1 || nextY > N || map[nextX][nextY] == 2) { //가만히 있음
				chessMap[startX][startY].push_back(chessIdx);
				chess[chessIdx].second = nextDir;
				if (chessMap[startX][startY].size() >= 4) {
					exitFlag = 1;
				}
			}
			else {
				chessMap[nextX][nextY].push_back(chessIdx);
				chess[chessIdx].first.first = nextX;
				chess[chessIdx].first.second = nextY;
				chess[chessIdx].second = nextDir;
				if (chessMap[nextX][nextY].size() >= 4) {
					exitFlag = 1;
				}
			}
		}
		else if (map[nextX][nextY] == 0 || map[nextX][nextY] == 1) {
			chessMap[nextX][nextY].push_back(chessIdx);
			chess[chessIdx].first.first = nextX;
			chess[chessIdx].first.second = nextY;
			if (chessMap[nextX][nextY].size() >= 4) {
				exitFlag = 1;
			}
		}
	}
	else {
		//이동할 체스말 -> move, 남을 체스 -> stay 큐에 각각 삽입
		while (1) {
			tmpIdx = chessMap[startX][startY].front();
			if (tmpIdx == chessIdx) break;
			else {
				chessMap[startX][startY].pop_front();
				stay.push(tmpIdx);
			}
		}
		while (!chessMap[startX][startY].empty()) {
			tmpIdx = chessMap[startX][startY].front();
			chessMap[startX][startY].pop_front();
			move.push_back(tmpIdx);
		}
		while (!stay.empty()) {
			tmpIdx = stay.front();
			chessMap[startX][startY].push_back(tmpIdx);
			stay.pop();
		}

		nextX = startX + dx[curDir];
		nextY = startY + dy[curDir];
		if (nextX < 1 || nextX > N || nextY < 1 || nextY > N || map[nextX][nextY] == 2) {
			if (curDir == 2 || curDir == 4) nextDir = curDir - 1;
			else nextDir = curDir + 1;

			nextX = startX + dx[nextDir];
			nextY = startY + dy[nextDir];
			if (nextX < 1 || nextX > N || nextY < 1 || nextY > N || map[nextX][nextY] == 2) { //가만히 있음
				while (!move.empty()) {
					tmpIdx = move.front();
					move.pop_front();
					chessMap[startX][startY].push_back(tmpIdx);
				}
				chess[chessIdx].second = nextDir;
				if (chessMap[startX][startY].size() >= 4) {
					exitFlag = 1;
				}
			}
			else if (map[nextX][nextY] == 0) {
				while (!move.empty()) {
					tmpIdx = move.front();
					move.pop_front();
					chessMap[nextX][nextY].push_back(tmpIdx);
					chess[tmpIdx].first.first = nextX;
					chess[tmpIdx].first.second = nextY;
				}
				chess[chessIdx].second = nextDir;
				if (chessMap[nextX][nextY].size() >= 4) {
					exitFlag = 1;
				}
			}
			else if (map[nextX][nextY] == 1) {
				while (!move.empty()) {
					tmpIdx = move.back();
					move.pop_back();
					chessMap[nextX][nextY].push_back(tmpIdx);
					chess[tmpIdx].first.first = nextX;
					chess[tmpIdx].first.second = nextY;
				}
				chess[chessIdx].second = nextDir;
				if (chessMap[nextX][nextY].size() >= 4) {
					exitFlag = 1;
				}
			}
		}
		else if (map[nextX][nextY] == 0) {
			while (!move.empty()) {
				tmpIdx = move.front();
				move.pop_front();
				chessMap[nextX][nextY].push_back(tmpIdx);
				chess[tmpIdx].first.first = nextX;
				chess[tmpIdx].first.second = nextY;
			}
			if (chessMap[nextX][nextY].size() >= 4) {
				exitFlag = 1;
			}

		}
		else if (map[nextX][nextY] == 1) {
			while (!move.empty()) {
				tmpIdx = move.back();
				move.pop_back();
				chessMap[nextX][nextY].push_back(tmpIdx);
				chess[tmpIdx].first.first = nextX;
				chess[tmpIdx].first.second = nextY;
			}
			if (chessMap[nextX][nextY].size() >= 4) {
				exitFlag = 1;
			}
		}
	}

}

void Solve() {
	int time = 0;
	while (1) {
		time++;

		for (int idx = 0; idx < K; idx++) {
			move_chess(idx, chess[idx].first.first, chess[idx].first.second, chess[idx].second);
			if (exitFlag == 1) break;
			//print();
		}

		//cout << time << "초 후" << endl;
		//print();

		if (exitFlag == 1) break;
		else if(time > 1000) break;

	}
	if (time > 1000) Answer = -1;
	else {
		Answer = time;
	}

}

void Input() {
	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}
	int tmpX, tmpY, tmpD;
	for (int chessIdx = 0; chessIdx < K; chessIdx++) {
		cin >> tmpX >> tmpY >> tmpD;
		chess.push_back(make_pair(make_pair(tmpX, tmpY), tmpD));
		chessMap[tmpX][tmpY].push_back(chessIdx);
	}
}

int main(void) {

	Input();
	Solve();

	cout << Answer << endl;

	return 0;
}