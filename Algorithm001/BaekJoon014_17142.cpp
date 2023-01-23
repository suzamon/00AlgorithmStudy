#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>
#include <cmath>

using namespace std;

int N, M, Answer = -1;
int map[51][51];
int emptyPlace = 0;
int copyMap[51][51];
int copyEmptyPlace = 0;
int chooseVirus[11];

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };


deque <pair <int, int>> virus;

void print_map() {
	cout << "맵 정보" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << copyMap[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

int check_empty() {
	int flag = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (copyMap[i][j] == 0) {
				flag = 1;
				break;
			}
		}
		if (flag != 0) break;
	}
	return flag;
}

void copy_map() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			copyMap[i][j] = map[i][j];
		}
	}
	copyEmptyPlace = emptyPlace;
}

void sim_virus() {
	int virusIdx, startX, startY, nextX, nextY, time;
	int checkFlag = 1;

	queue <pair <int, pair<int, int>>> v;

	for (int i = 0; i < M; i++) {
		virusIdx = chooseVirus[i];
		startX = virus[virusIdx].first;
		startY = virus[virusIdx].second;
		copyMap[startX][startY] = 2;
		v.push(make_pair(2, make_pair(startX, startY)));
	}

	while (!v.empty()) {
		time = v.front().first;
		startX = v.front().second.first;
		startY = v.front().second.second;
		v.pop();

		if (copyEmptyPlace <= virus.size() - M) {
			checkFlag = check_empty();
			if (checkFlag == 0) {
				break;
			}
		}

		for (int i = 0; i < 4; i++) {
			nextX = startX + dx[i];
			nextY = startY + dy[i];
			if (nextX >= 0 && nextX < N && nextY >= 0 && nextY < N) {
				if (copyMap[nextX][nextY] == 0) {
					copyMap[nextX][nextY] = time + 1;
					v.push(make_pair(time + 1, make_pair(nextX, nextY)));
					copyEmptyPlace--;
				}
				else if (copyMap[nextX][nextY] == -1) {
					copyMap[nextX][nextY] = time + 1;
					v.push(make_pair(time + 1, make_pair(nextX, nextY)));
				}
			}
		}
	}
	if (checkFlag == 0) {
		while (!v.empty()) {
			time = v.front().first;
			v.pop();
		}
		if (Answer == -1) {
			Answer = time - 2;
			//cout << "Answer1 : " << Answer << endl;
			//print_map();
		}
		else if (Answer > time - 2) {
			Answer = time - 2;
			//cout << "Answer1 : " << Answer << endl;
			//print_map();
		}
	}
	else {
		checkFlag = check_empty();
		if (checkFlag == 0 && Answer == -1) {
			Answer = time - 2;
			//cout << "Answer2 : " << Answer << endl;
			//print_map();
		}
		else if (checkFlag == 0 && Answer > time - 2) {
			Answer = time - 2;
			//cout << "Answer2 : " << Answer << endl;
			//print_map();
		}
	}
}

void DFS(int start, int cnt) {
	if (cnt == M) {
		/*
		cout << "바이러스 선택" << endl;
		for (int i = 0; i < M; i++) {
			cout << chooseVirus[i] << ", ";
		}
		cout << endl;
		*/
		copy_map();

		sim_virus();

		//print_map();

		return;
	}

	for (int i = start; i < virus.size(); i++) {
		chooseVirus[cnt] = i;
		DFS(i + 1, cnt + 1);
	}
}

void Solve() {
	for (int i = 0; i <= virus.size() - M; i++) {
		chooseVirus[0] = i;
		DFS(i + 1, 1);
	}

}

void Input() {
	cin >> N >> M;
	int tmp;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				virus.push_back(make_pair(i, j));
				map[i][j] = -1;
			}
			else if (map[i][j] == 0) {
				emptyPlace++;
			}
		}
	}
}


int main(void) {
	Input();
	Solve();
	cout << Answer << endl;
	return 0;
}