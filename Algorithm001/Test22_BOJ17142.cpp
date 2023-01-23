#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int N, M, originEmptyCnt, emptyCnt, Answer = -1;
int originalMap[51][51] = { 0, };
int map[51][51] = { 0, };

int activeIdx[11] = { 0, };

int dx[5] = { 0, -1, 0, 1, 0 };
int dy[5] = { 0, 0, 1, 0, -1 };

deque <pair <int, int>> virusPos;

bool inRange(int xx, int yy) {
	if (xx > 0 && xx <= N && yy > 0 && yy <= N) return true;
	return false;
}

void copyMap() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			map[i][j] = originalMap[i][j];
		}
	}
	emptyCnt = originEmptyCnt;
}

void simualtion() {
	int tmpIdx, sX, sY, nX, nY, dir, time, minTime = -1;
	
	queue <pair <int, pair<int, int>>> q;

	time = 3;
	for (int i = 0; i < M; i++) {
		tmpIdx = activeIdx[i];
		q.push(make_pair(time, make_pair(virusPos[tmpIdx].first, virusPos[tmpIdx].second)));
		map[virusPos[tmpIdx].first][virusPos[tmpIdx].second] = time;
	}

	while (!q.empty()) {
		time = q.front().first;
		sX = q.front().second.first, sY = q.front().second.second;
		q.pop();

		if (emptyCnt == 0) {
			continue;
		}

		for (dir = 1; dir <= 4; dir++) {
			nX = sX + dx[dir], nY = sY + dy[dir];
			if (!inRange(nX, nY)) continue;

			if (map[nX][nY] == 0) {
				map[nX][nY] = time + 1;
				emptyCnt--;
				q.push(make_pair(time + 1, make_pair(nX, nY)));
				if (emptyCnt == 0) {
					minTime = time + 1;
					break;
				}
			}
			else if (map[nX][nY] == 2) {
				map[nX][nY] = time + 1;
				q.push(make_pair(time + 1, make_pair(nX, nY)));
			}
		}
	}
	if (minTime == -1) return;
	
	if (Answer == -1) {
		Answer = minTime - 3;
	}
	else if (Answer > (minTime - 3)) {
		Answer = minTime - 3;
	}
	return;
}

void find_active(int idx, int cnt) {
	if (cnt == M) {
		copyMap();
		simualtion();
		return;
	}
	for (int i = idx; i <= virusPos.size() - M + cnt; i++) {
		activeIdx[cnt] = i;
		find_active(i + 1, cnt + 1);
	}
}

void Solution() {
	if (originEmptyCnt == 0) {
		Answer = 0;
		cout << Answer << endl;
		return;
	}
	for (int i = 0; i <= virusPos.size() - M; i++) {
		activeIdx[0] = i;
		find_active(i + 1, 1);
	}
	cout << Answer << endl;
}

void Input() {
	cin >> N >> M;
	originEmptyCnt = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> originalMap[i][j];
			if (originalMap[i][j] == 2) virusPos.push_back(make_pair(i, j));
			else if (originalMap[i][j] == 0) originEmptyCnt++;
		}
	}
}


int main(void) {
	Input();
	Solution();
	return 0;
}