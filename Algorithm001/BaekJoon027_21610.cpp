#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <deque>
#include <cmath>

using namespace std;

int N, M, Answer = 0;
int map[51][51];
int visited[51][51];
int command[101][2];
deque <pair <int, int>> cloud;
deque <pair<int, int>> eCloud;

int dx[9] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 }; //←, ↖, ↑, ↗, →, ↘, ↓, ↙
int dy[9] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 }; //←, ↖, ↑, ↗, →, ↘, ↓, ↙

int crossDx[4] = { -1, -1, 1, 1 }; // ↖, ↗, ↘, ↙
int crossDy[4] = { -1, 1, 1, -1 }; // ↖, ↗, ↘, ↙

void print() {
	cout << "Map" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	cout << "구름 정보" << endl;
	for (int i = 0; i < cloud.size(); i++) {
		cout << i << "번째 구름: (" << cloud[i].first << ", " << cloud[i].second << ")에 존재" << endl;
	}
	cout << endl;
	cout << "제거된 구름 정보" << endl;
	for (int i = 0; i < eCloud.size(); i++) {
		cout << i << "번째 구름: (" << eCloud[i].first << ", " << eCloud[i].second << ")에 존재" << endl;
	}
	cout << endl;
}

void find_answer() {
	Answer = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			Answer += map[i][j];
		}
	}
}

void add_cloud() {
	//구름 추가
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j] >= 2 && visited[i][j] == 0) {
				map[i][j] -= 2;
				cloud.push_back(make_pair(i, j));
			}
		}
	}

	int startX, startY, eCloudSize;
	eCloudSize = eCloud.size();
	for (int i = 0; i < eCloudSize; i++) {
		startX = eCloud.front().first;
		startY = eCloud.front().second;
		eCloud.pop_front();

		visited[startX][startY] = 0;
	}
}

void water_magic() {
	int startX, startY, nextX, nextY, waterCnt;

	for (int i = 0; i < eCloud.size(); i++) {
		startX = eCloud[i].first;
		startY = eCloud[i].second;

		waterCnt = 0;

		for (int d = 0; d < 4; d++) {
			nextX = startX + crossDx[d];
			nextY = startY + crossDy[d];
			if (nextX >= 1 && nextX <= N && nextY >= 1 && nextY <= N && map[nextX][nextY] >= 1) {
				waterCnt++;
			}
		}

		map[startX][startY] += waterCnt;
	}
}

void remove_cloud() {
	int row, col;
	int cloudSize = cloud.size();

	for (int i = 0; i < cloudSize; i++) {
		row = cloud.front().first;
		col = cloud.front().second;
		cloud.pop_front();
		eCloud.push_back(make_pair(row, col));
		visited[row][col] = 1;
	}
}

void add_water() {
	int row, col;
	for (int i = 0; i < cloud.size(); i++) {
		row = cloud[i].first;
		col = cloud[i].second;

		map[row][col] += 1;
	}
}

void move_cloud(int dir, int size) {
	int startX, startY, nextX, nextY;

	for (int i = 0; i < cloud.size(); i++) {
		startX = cloud[i].first;
		startY = cloud[i].second;

		nextX = startX + dx[dir] * size;
		nextY = startY + dy[dir] * size;

		while (nextX < 1) {
			nextX += N;
		}
		while (nextX > N) {
			nextX -= N;
		}

		while (nextY < 1) {
			nextY += N;
		}
		while (nextY > N) {
			nextY -= N;
		}

		cloud[i].first = nextX;
		cloud[i].second = nextY;
	}
}

void Solution() {
	//print();
	/*
	move_cloud(command[1][0], command[1][1]);
	cout << "구름 이동 후" << endl;
	print();
	add_water();
	cout << "물 뿌린 후" << endl;
	print();
	remove_cloud();
	cout << "구름 제거 후" << endl;
	print();
	water_magic();
	cout << "마법 후" << endl;
	print();
	add_cloud();
	cout << "구름 추가 후" << endl;
	print();
	*/
	
	int time = 0;
	while (1) {
		time++;
		if (time == M + 1) break;
		move_cloud(command[time][0], command[time][1]);
		add_water();
		remove_cloud();

		water_magic();
		add_cloud();

		//cout << time << "초 후" << endl;
		//print();
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

	for (int i = 1; i <= M; i++) {
		cin >> command[i][0] >> command[i][1];
	}

	cloud.push_back(make_pair(N, 1));
	cloud.push_back(make_pair(N, 2));
	cloud.push_back(make_pair(N - 1, 1));
	cloud.push_back(make_pair(N - 1, 2));
}

int main(void) {
	Input();

	Solution();

	cout << Answer << endl;

	return 0;
}