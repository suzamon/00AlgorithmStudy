#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <deque>
#include <cmath>

using namespace std;

int N, M, K, Answer = 0;
int map[21][21][2];

deque <pair <int, pair<pair <int, int>, pair <int, int>>>> shark;
int priority[401][5][4];

int dx[5] = { 0, -1, 1, 0, 0 };
int dy[5] = { 0, 0, 0, -1, 1 };

void print_inf() {
	cout << "맵 정보" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j][0] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	cout << "맵 정보2" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j][1] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	cout << "상어 정보" << endl;
	for (int i = 0; i < shark.size(); i++) {
		if (shark[i].second.second.second == 1) {
			cout << shark[i].first << "번 상어는 죽었습니다." << endl;
		}
		cout << shark[i].first << "번 상어 정보: (" << shark[i].second.first.first << ", " << shark[i].second.first.second << "), 상어 방향: " << shark[i].second.second.first << endl;
	}
	cout << endl;
}

void update_map() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j][0] != 0) {
				map[i][j][1]--;
				if (map[i][j][1] == 0) {
					map[i][j][0] = 0;
				}
			}
		}
	}
}

void update_shark() {
	int sharkSize = shark.size();
	int sharkNum, sharkX, sharkY, sharkDir, sharkState;

	for (int idx = 0; idx < sharkSize; idx++) {
		sharkNum = shark.front().first;
		sharkX = shark.front().second.first.first;
		sharkY = shark.front().second.first.second;
		sharkDir = shark.front().second.second.first;
		sharkState = shark.front().second.second.second;
		shark.pop_front();

		if (map[sharkX][sharkY][0] == 0) {
			map[sharkX][sharkY][0] = sharkNum;
			map[sharkX][sharkY][1] = K + 1;
			shark.push_back(make_pair(sharkNum, make_pair(make_pair(sharkX, sharkY), make_pair(sharkDir, sharkState))));
		}
		else if (map[sharkX][sharkY][0] == sharkNum) {
			map[sharkX][sharkY][0] = sharkNum;
			map[sharkX][sharkY][1] = K + 1;
			shark.push_back(make_pair(sharkNum, make_pair(make_pair(sharkX, sharkY), make_pair(sharkDir, sharkState))));
		}

	}
}

void find_shark_pos() {
	int sharkSize = shark.size();
	int sharkNum;
	int curX, curY, curDir, nextX, nextY, nextDir, tmpCnt, tmpFlag = 0;

	for (int idx = 0; idx < sharkSize; idx++) {
		if (shark[idx].second.second.second == 1) continue;
		tmpFlag = 0;
		sharkNum = shark[idx].first;
		curX = shark[idx].second.first.first;
		curY = shark[idx].second.first.second;
		curDir = shark[idx].second.second.first;

		for (tmpCnt = 0; tmpCnt < 4; tmpCnt++) {
			nextDir = priority[sharkNum-1][curDir][tmpCnt];
			nextX = curX + dx[nextDir];
			nextY = curY + dy[nextDir];
			if (nextX >= 0 && nextX < N && nextY >= 0 && nextY < N && map[nextX][nextY][0] == 0) {
				shark[idx].second.first.first = nextX;
				shark[idx].second.first.second = nextY;
				shark[idx].second.second.first = nextDir;
				break;
			}
			
			if (tmpCnt == 3) tmpFlag = 1;
		}

		if (tmpFlag == 1) {
			for (tmpCnt = 0; tmpCnt < 4; tmpCnt++) {
				nextDir = priority[sharkNum - 1][curDir][tmpCnt];
				nextX = curX + dx[nextDir];
				nextY = curY + dy[nextDir];
				if (nextX >= 0 && nextX < N && nextY >= 0 && nextY < N && map[nextX][nextY][0] == sharkNum) {
					break;
				}
			}
			shark[idx].second.first.first = nextX;
			shark[idx].second.first.second = nextY;
			shark[idx].second.second.first = nextDir;
		}
		
	}
}

void Solve() {
	int sharkSize, time = 0;

	while (1) {
		time++;
		if (time > 1000) break;
		find_shark_pos();
		update_shark();
		update_map();
		//cout << time << "초 후" << endl;
		//print_inf();

		sharkSize = shark.size();
		if (sharkSize == 1) break;
	}
	if (time <= 1000) {
		Answer = time;
	}
	else {
		Answer = -1;
	}
}


bool compare(pair <int, pair<pair <int, int>, pair <int, int>>> a, pair <int, pair<pair <int, int>, pair <int, int>>> b) {
	return a.first < b.first;
}

void Input() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j][0];
			if (map[i][j][0] != 0) {
				map[i][j][1] = K;
				shark.push_back(make_pair(map[i][j][0], make_pair(make_pair(i, j), make_pair(0, 0))));
			}
		}
	}
	sort(shark.begin(), shark.end(), compare);
	int tmp;
	for (int i = 0; i < M; i++) {
		cin >> tmp;
		shark[i].second.second.first = tmp;
	}
	for (int i = 0; i < M; i++) {
		for (int j = 1; j < 5; j++) {
			for (int k = 0; k < 4; k++) {
				cin >> priority[i][j][k];
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