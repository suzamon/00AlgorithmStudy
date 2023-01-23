#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <deque>
#include <cmath>

using namespace std;

int N, M;
int map[21][21];

int dx[4] = { -1, 1, 0, 0 }; //상하좌우
int dy[4] = { 0, 0, -1, 1 }; //상하좌우

deque <pair<int, int>> rainbowBlock;

void print_map() {
	cout << "Map 정보" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

bool compare(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b) {
	if (a.first.second == b.first.second) {
		if (a.second.first == b.second.first) {
			return a.second.second < b.second.second;
		}
		return a.second.first < b.second.second;
	}
	return a.first.second > b.first.second;
}


deque <int> find_bfs(int x, int y, int color) {
	int visit[21][21] = { 0, };

	deque <pair<int, int>> q;

	q.push_back(make_pair(x, y));
	visit[x][y] = 1;
	int normalBlockCnt = 0, blockCnt = 1;

	int startX, startY, nextX, nextY;
	int standX = -1, standY = -1;
	while (!q.empty()) {
		startX = q.front().first;
		startY = q.front().second;
		q.pop_front();
		for (int d = 0; d < 4; d++) {
			nextX = startX + dx[d];
			nextY = startY + dy[d];
			if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N || visit[nextX][nextY] == 1) continue;
			
			if (map[nextX][nextY] == 0) {
				blockCnt++;
				q.push_back(make_pair(nextX, nextY));
				visit[nextX][nextY] = 1;
			}
			else if (map[nextX][nextY] == color) {
				if (standX == -1 && standY == -1) {
					standX = nextX;
					standY = nextY;
				}
				else if(nextX < standX){
					standX = nextX;
					standY = nextY;
				}
				else if (nextX == standX && nextY < standY) {
					standX = nextX;
					standY = nextY;
				}

				normalBlockCnt++;
				blockCnt++;
				q.push_back(make_pair(nextX, nextY));
				visit[nextX][nextY] = 1;
			}
		}
	}
	deque <int> d;

	if (normalBlockCnt < 1) {
		return d;
	}
	else {
		d.push_back(blockCnt);
		d.push_back(standX);
		d.push_back(standY);
		return d;
	}
}

void find_max_block() {
	//deque <pair<pair<int, int>, pair<int, int>>> tmpBlockGroup[401];
	deque <pair <int, int>> rainbowGroup[401];
	deque <pair<int, int>> tmp;
	int nearColor[401][6] = { 0, };
	int arr[401][4] = { 0, }; //일반그룹 색깔, size, standardX, standardY
	int visited[21][21] = { 0, };

	int tmpCnt = 0, rainbowSize, startX, startY, nextX, nextY;
	//1. 무지개 블록으로 구성된 그룹 찾기
	rainbowSize = rainbowBlock.size();
	for (int i = 0; i < rainbowSize; i++) {
		startX = rainbowBlock.front().first;
		startY = rainbowBlock.front().second;
		rainbowBlock.pop_front();
		if (visited[startX][startY] == 1) continue;
		
		visited[startX][startY] = 1;
		//tmpBlockGroup[tmpCnt].push_back(make_pair(make_pair(0, 0), make_pair(startX, startY)));
		rainbowGroup[tmpCnt].push_back(make_pair(startX, startY));
		tmp.push_back(make_pair(startX, startY));
		while (!tmp.empty()) {
			startX = tmp.front().first;
			startY = tmp.front().second;
			tmp.pop_back();
			for (int d = 0; d < 4; d++) {
				nextX = startX + dx[d];
				nextY = startY + dy[d];
				if (nextX >= 0 && nextX < N && nextY >= 0 && nextY < N && map[nextX][nextY] == 0 && visited[nextX][nextY] == 0) {
					visited[nextX][nextY] = 1;
					//tmpBlockGroup[tmpCnt].push_back(make_pair(make_pair(0, 0), make_pair(nextX, nextY)));
					rainbowGroup[tmpCnt].push_back(make_pair(nextX, nextY));
					tmp.push_back(make_pair(nextX, nextY));
				}
				else if (nextX >= 0 && nextX < N && nextY >= 0 && nextY < N && map[nextX][nextY] > 0) {
					nearColor[tmpCnt][map[nextX][nextY]] = 1;
				}
			}
		}

		tmpCnt++;
	}

	cout << "무지개 블록 그룹" << endl;
	for (int i = 0; i < tmpCnt; i++) {
		cout << i << "번째 그룹" << endl;
		for (int j = 0; j < rainbowGroup[i].size(); j++) {
			cout <<'('<< rainbowGroup[i][j].first << ", " << rainbowGroup[i][j].second << "), " << endl;
		}
	}

	//2. 각 블록별 일반색에 따른 가장 큰 블록 그룹 탐색
	int groupColor = 0;
	deque <int> tmpGroup;

	deque <pair<pair<int, int>, pair<int, int>>> blockGroup; // 일반그룹 색깔, 사이즈, standardX, standartY

	for (int i = 0; i < tmpCnt; i++) {
		for (int j = 1; j <= M; j++) {
			if (nearColor[i][j] == 1) {
				tmpGroup = find_bfs(rainbowGroup[i].front().first, rainbowGroup[i].front().second, j);
				if (tmpGroup.size() == 0) continue;

				if (arr[i][0] == 0) {
					arr[i][0] = j;
					arr[i][1] = tmpGroup[0];
					arr[i][2] = tmpGroup[1];
					arr[i][3] = tmpGroup[2];
				}
				else if (arr[i][1] < tmpGroup[0]) {
					arr[i][0] = j;
					arr[i][1] = tmpGroup[0];
					arr[i][2] = tmpGroup[1];
					arr[i][3] = tmpGroup[2];
				}
				else if (arr[i][1] == tmpGroup[0]) {
					if (arr[i][2] > tmpGroup[1]) {
						arr[i][0] = j;
						arr[i][1] = tmpGroup[0];
						arr[i][2] = tmpGroup[1];
						arr[i][3] = tmpGroup[2];
					}
					else if (arr[i][2] == tmpGroup[1] && arr[i][3] > tmpGroup[2]) {
						arr[i][0] = j;
						arr[i][1] = tmpGroup[0];
						arr[i][2] = tmpGroup[1];
						arr[i][3] = tmpGroup[2];
					}
				}
			}
		}

		blockGroup.push_back(make_pair(make_pair(arr[i][0], arr[i][1]), make_pair(arr[i][2], arr[i][3])));
	}

	if (blockGroup.size() == 0) {
		//끝
		return;
	}

	sort(blockGroup.begin(), blockGroup.end(), compare);

	cout << "가장 큰 블록" << endl;
	cout << blockGroup.front().first.first << "번 색을 가진 블록 그룹이며 사이즈는: " << blockGroup.front().first.second << ", 기준 블록: (" << blockGroup.front().second.first << ", " << blockGroup.front().second.second << ')'<< endl;
}

void find_rainbow_block() {
	rainbowBlock.clear();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 0) {
				rainbowBlock.push_back(make_pair(i, j));
			}
		}
	}
}

void Solution() {
	int time = 0;
	while (1) {
		time++;
		if (time > 1) find_rainbow_block();


	}
}

void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0) {
				rainbowBlock.push_back(make_pair(i, j));
			}
		}
	}
}

int main(void) {
	Input();

	find_max_block();
	return 0;
}