#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

struct shark {
	int xx, yy, size, fishCnt;
}s;

int N, fishCnt = 0, Answer = 0;
int map[21][21], fish[7] = { 0, };

int dx[5] = { 0, -1, 0, 1, 0 };
int dy[5] = { 0, 0, -1, 0, 1 };

void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				s.xx = i, s.yy = j, s.size = 2, s.fishCnt = 0;
				map[i][j] = 0;
			}
			else if (map[i][j] > 0 && map[i][j] < 7) {
				fish[map[i][j]]++;
				fishCnt++;
			}
		}
	}
}

int check_flag() {
	if (fishCnt == 0) return 1;

	int sharkSize = s.size;
	for (int i = sharkSize - 1; i > 0; i--) {
		if (fish[i] > 0) return 0;
	}
	return 1;
}

bool inRange(int xx, int yy) {
	if (xx > 0 && xx <= N && yy > 0 && yy <= N) return true;
	return false;
}

int find_fish() {
	int sX, sY, sSize, fCnt, nX, nY, dir, tmpTime;
	int fX = 0, fY = 0, addTime = 0;

	int visited[21][21] = { 0, };

	queue <pair <int, pair <int, int>>> q;

	sX = s.xx, sY = s.yy, sSize = s.size, fCnt = s.fishCnt;
	q.push(make_pair(0, make_pair(sX, sY)));
	visited[sX][sY] = 1;

	while (!q.empty()) {
		tmpTime = q.front().first;
		sX = q.front().second.first, sY = q.front().second.second;
		q.pop();

		if (addTime != 0 && addTime <= tmpTime) continue;

		for (int d = 1; d <= 4; d++) {
			nX = sX + dx[d], nY = sY + dy[d];
			if (!inRange(nX, nY) || visited[nX][nY] == 1) continue;

			if (map[nX][nY] == 0 || map[nX][nY] == sSize) {
				visited[nX][nY] = 1;
				q.push(make_pair(tmpTime + 1, make_pair(nX, nY)));
			}
			else if (map[nX][nY] < sSize) {
				visited[nX][nY] = 1;
				if (addTime == 0) {
					addTime = tmpTime + 1;
					fX = nX, fY = nY;
				}
				else {
					if (addTime > (tmpTime + 1)) {
						addTime = tmpTime + 1;
						fX = nX, fY = nY;
					}
					else if (addTime == (tmpTime + 1) && fX > nX) {
						addTime = tmpTime + 1;
						fX = nX, fY = nY;
					}
					else if (addTime == (tmpTime + 1) && fX == nX && fY > nY) {
						addTime = tmpTime + 1;
						fX = nX, fY = nY;
					}
				}
			}
		}
	}

	if (fX == 0 && fY == 0) return -1;

	s.xx = fX, s.yy = fY;
	fCnt++;
	if (fCnt == sSize) {
		s.size = sSize + 1;
		s.fishCnt = 0;
	}
	else {
		s.fishCnt = fCnt;
	}

	fishCnt--;
	fish[map[fX][fY]] = fish[map[fX][fY]] - 1;
	map[fX][fY] = 0;

	return addTime;

}

void Solution() {
	int time = 0, addTime, exitFlag;

	while (1) {
		exitFlag = check_flag();
		if (exitFlag == 1) break;
		
		addTime = find_fish();
		if (addTime == -1) break;
		time = time + addTime;
	}

	Answer = time;
	cout << Answer << endl;
}

int main(void) {
	Input();
	Solution();
	return 0;
}