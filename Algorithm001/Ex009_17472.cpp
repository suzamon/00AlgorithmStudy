/*
섬으로 이루어진 나라가 있고, 모든 섬을 다리로 연결하려고 한다.
이 나라의 지도는 N×M 크기의 이차원 격자로 나타낼 수 있고, 격자의 각 칸은 땅이거나 바다
섬은 연결된 땅이 상하좌우로 붙어있는 덩어리
다리는 바다에만 건설할 수 있고, 다리의 길이는 다리가 격자에서 차지하는 칸의 수
다리를 연결해서 모든 섬을 연결하려고 한다. 섬 A에서 다리를 통해 섬 B로 갈 수 있을 때, 섬 A와 B를 연결되었다
다리의 양 끝은 섬과 인접한 바다 위에 있어야 하고, 한 다리의 방향이 중간에 바뀌면 안된다.
다리의 길이는 2 이상이어야 한다.

다리의 방향이 중간에 바뀌면 안되기 때문에,
다리의 방향은 가로 또는 세로
-> 방향이 가로인 다리는 다리의 양 끝이 가로 방향으로 섬과 인접
-> 방향이 세로인 다리는 다리의 양 끝이 세로 방향으로 섬과 인접
섬 A와 B를 연결하는 다리가 중간에 섬 C와 인접한 바다를 지나가는 경우에 섬 C는 A, B와 연결되어있는 것이 아니다.
다리가 교차하는 경우가 있을 수도 있다. 교차하는 다리의 길이를 계산할 때는 각 칸이 각 다리의 길이에 모두 포함

Answer : 모든 섬을 연결하는 다리 길이의 최솟값을 출력한다. 모든 섬을 연결하는 것이 불가능하면 -1을 출력

첫째 줄에 지도의 세로 크기 N과 가로 크기 M
둘째 줄부터 N개의 줄에 지도의 정보가 주어진다.
각 줄은 M개의 수로 이루어져 있으며, 수는 0 또는 1이다. 0은 바다, 1은 땅을 의미

1 ≤ N, M ≤ 10
3 ≤ N×M ≤ 100
2 ≤ 섬의 개수 ≤ 6

모두 연결 -> N-1 개의 다리

1. Input() : map[N][M], visited[N][M], islandCnt, connectMap[6][6], deque <int, int> island[6] -> 각 섬별 왼쪽 위, 오른쪽 아래 위치 저장


2. Solution():
	1) check_island()
		: BFS로 각 섬 갯수 탐색 & 맵에 1~6까지 표시 & islandCnt에 섬 갯수 저장
		: islandCnt, map에 표시, connectMap 초기화, deque island에 idx별 섬 위치 정보 저장
	2) find_connect_island(int startIdx) -> possible[6][6][4] =>
		: 필요한 정보 ->
		 possible[startIdx][endIdx][0] (다른 섬과 연결 가능성 0: 불가, 1: 가능),
		 possible[startIdx][endIdx][1] -> 최소 다리 길이,
		 possible[startIdx][endIdx][2][3] -> 연결할 때, row, col 값
	3) connect_island
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int N, M, islandCnt, Answer = 99999;
int map[11][11] = { 0, };
int visited[11][11] = { 0, };
int connectMap[7][7] = { 0, };
int possible[7][7][4] = { 0, };

deque <pair <int, int>> island[7]; //섬 idx별 좌표 저장
deque <pair <int, int>> dq;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void print_conncet_map() {
	cout << "conncetion Map" << endl;
	for (int i = 1; i <= islandCnt; i++) {
		for (int j = 1; j <= islandCnt; j++) {
			cout << connectMap[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void print_map() {
	cout << "Map" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 1; i <= islandCnt; i++) {
		cout << i << "번 섬 크기: " << island[i].size() << endl;
		for (int j = 1; j <= islandCnt; j++) {
			cout << j << "번 섬과 연결 가능성: " << possible[i][j][0] << endl;
			if (possible[i][j][0] == 1) {
				cout << "최소 다리 길이: " << possible[i][j][1] << ", 연결 포인트: (" << possible[i][j][2] << ", " << possible[i][j][3] << ')' << endl;
			}
		}
		cout << endl;
	}
}

bool inRange(int r, int c) {
	if (r >= 0 && r < N && c >= 0 && c < M) return true;
	else return false;
}

void connect_island(int sidx, int eidx, int cnt, int totalLength) {
	if (cnt == islandCnt - 1) {
		if (totalLength == 0) return;
		
		Answer = min(Answer, totalLength);
		//cout << cnt << ", "<<totalLength<<endl;
		//print_conncet_map();
		return;
	}

	if (eidx > islandCnt) {
		sidx++;
		eidx = 1;
		if (sidx > islandCnt) return;
	}
	deque <pair <int, int>> tmp;
	int tmpIdx1, tmpIdx2;
	for (int i = eidx; i <= islandCnt; i++) {
		if (sidx == i || connectMap[sidx][i] == 1 || connectMap[i][sidx] == 1) continue;

		if (possible[sidx][i][0] == 1) {
			connectMap[sidx][i] = 1;
			for (int j = 1; j < 6; j++) {
				if (i != j && j != sidx && connectMap[i][j] == 1 && connectMap[sidx][j] == 0) {
					connectMap[sidx][j] = 1;
					connectMap[j][sidx] = 1;
					tmp.push_back(make_pair(sidx, j));
				}
			}
			connectMap[i][sidx] = 1;
			for (int j = 1; j < 6; j++) {
				if (sidx != j && j != i && connectMap[sidx][j] == 1 && connectMap[i][j] == 0) {
					connectMap[i][j] = 1;
					connectMap[j][i] = 1;
					tmp.push_back(make_pair(i, j));
				}
			}
			connect_island(sidx, i + 1, cnt + 1, totalLength + possible[sidx][i][1]);
			connectMap[sidx][i] = 0;
			connectMap[i][sidx] = 0;
			while (!tmp.empty()) {
				tmpIdx1 = tmp.front().first;
				tmpIdx2 = tmp.front().second;
				tmp.pop_front();
				connectMap[tmpIdx1][tmpIdx2] = 0;
				connectMap[tmpIdx2][tmpIdx1] = 0;
			}
		}
		if (i == islandCnt) connect_island(sidx, i + 1, cnt, totalLength);
	}

}

void find_connect_island(int startIdx) {
	int startX, startY, nextX, nextY, nextIdx, length;

	for (int i = 0; i < island[startIdx].size(); i++) {
		startX = island[startIdx][i].first;
		startY = island[startIdx][i].second;
		for (int d = 0; d < 4; d++) {
			nextX = startX;
			nextY = startY;
			length = 0;
			while (1) {
				nextX = nextX + dx[d];
				nextY = nextY + dy[d];
				if (!inRange(nextX, nextY)) break;
				if (map[nextX][nextY] == startIdx) break;
				else if (map[nextX][nextY] == 0) {
					length++;
					continue;
				}
				else { //다른 섬 만났을 때
					if (length < 2) break;
					nextIdx = map[nextX][nextY];
					if (possible[startIdx][nextIdx][0] == 0) {
						possible[startIdx][nextIdx][0] = 1;
						possible[startIdx][nextIdx][1] = length;
						possible[startIdx][nextIdx][2] = startX;
						possible[startIdx][nextIdx][3] = startY;
					}
					else if (length < possible[startIdx][nextIdx][1]) {
						possible[startIdx][nextIdx][1] = length;
						possible[startIdx][nextIdx][2] = startX;
						possible[startIdx][nextIdx][3] = startY;
					}
					break;
				}
				
			}

		}
	}

}

void check_island() {
	int startX, startY, nextX, nextY, dqSize, i, j;
	dqSize = dq.size();

	queue <pair <int, int>> q;
	islandCnt = 1;

	for (i = 0; i < dqSize; i++) {
		startX = dq.front().first;
		startY = dq.front().second;
		dq.pop_front();
		if (visited[startX][startY] == 1) continue;

		visited[startX][startY] = 1;
		map[startX][startY] = islandCnt;
		island[islandCnt].push_back(make_pair(startX, startY));
		q.push(make_pair(startX, startY));

		while (!q.empty()) {
			startX = q.front().first;
			startY = q.front().second;
			q.pop();
			for (int d = 0; d < 4; d++) {
				nextX = startX + dx[d];
				nextY = startY + dy[d];
				if (!inRange(nextX, nextY)) continue;

				if (map[nextX][nextY] == 1 && visited[nextX][nextY] == 0) {
					visited[nextX][nextY] = 1;
					map[nextX][nextY] = islandCnt;
					q.push(make_pair(nextX, nextY));
					island[islandCnt].push_back(make_pair(nextX, nextY));
				}

			}
		}
		islandCnt++;
	}

	islandCnt--;

}

void Solution() {
	check_island();
	for (int i = 1; i <= islandCnt; i++) {
		find_connect_island(i);
	}
	//print_map();

	connect_island(1, 1, 0, 0);
}

void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) dq.push_back(make_pair(i, j));
		}
	}
}

int main(void) {
	Input();
	Solution();
	if (Answer == 99999) Answer = -1;
	cout << Answer << endl;
	return 0;
}