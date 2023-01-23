#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

struct cctv {
	int type, xx, yy, dir;
	cctv(int type, int xx, int yy, int dir) {
		this->xx = xx;
		this->yy = yy;
		this->dir = dir;
	}
};

struct cctvRegion {
	int sX, sY, dir;

	cctvRegion(int xx, int yy, int d) {
		this->sX = xx, this->sY = yy, this->dir = d;
	}
};

int N, M, emptyCnt = 0, copyEmptyCnt = 0, Answer = -1;
int originMap[9][9], map[9][9];

deque <cctv> dq;
deque <cctvRegion> dq2;

int dx[5] = { 0, -1, 0, 1, 0 };
int dy[5] = { 0, 0, 1, 0, -1 };

void print_info() {
	cout << "¿øº» ¸Ê: " << emptyCnt <<" °³ ºó °÷"<< endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << originMap[i][j] << ' ';
		}
		cout << endl;
	}

	cout << "¸Ê: " << copyEmptyCnt << " °³ ºó °÷" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
}

bool inRange(int xx, int yy) {
	if (xx >= 0 && xx < N && yy >= 0 && yy < M) return true;
	return false;
}

void set_origin_map() {
	int sX, sY, nX, nY, dir;
	while (!dq2.empty()) {
		nX = dq2.front().sX, nY = dq2.front().sY, dir = dq2.front().dir;
		dq2.pop_front();
		while (1) {
			nX = nX + dx[dir], nY = nY + dy[dir];
			if (!inRange(nX, nY) || originMap[nX][nY] == 6) break;
			else if (originMap[nX][nY] == 0) {
				emptyCnt--;
				originMap[nX][nY] = 9;
			}
		}
	}
}

void set_map() {
	int sX, sY, nX, nY, dir;
	while (!dq2.empty()) {
		nX = dq2.front().sX, nY = dq2.front().sY, dir = dq2.front().dir;
		dq2.pop_front();
		while (1) {
			nX = nX + dx[dir], nY = nY + dy[dir];
			if (!inRange(nX, nY) || map[nX][nY] == 6) break;
			else if (map[nX][nY] == 0) {
				copyEmptyCnt--;
				map[nX][nY] = 9;
			}
		}
	}
}

void copy_map() {
	copyEmptyCnt = emptyCnt;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			map[i][j] = originMap[i][j];
		}
	}
}

void simulation() {
	int type, sX, sY, dir;
	for (int i = 0; i < dq.size(); i++) {
		type = dq[i].type, sX = dq[i].xx, sY = dq[i].yy, dir = dq[i].dir;
		switch (type) {
		case 1:
			dq2.push_back(cctvRegion(sX, sY, dir));
			break;

		case 2:
			if (dir == 1) {
				dq2.push_back(cctvRegion(sX, sY, 2));
				dq2.push_back(cctvRegion(sX, sY, 4));
			}
			else {
				dq2.push_back(cctvRegion(sX, sY, 1));
				dq2.push_back(cctvRegion(sX, sY, 3));
			}
			break;
		case 3:
			if (dir == 4) {
				dq2.push_back(cctvRegion(sX, sY, dir));
				dq2.push_back(cctvRegion(sX, sY, 1));
			}
			else {
				for (int d = dir; d <= dir + 1; d++) {
					dq2.push_back(cctvRegion(sX, sY, d));
				}
			}
			break;
		case 4:
			if (dir == 1) {
				for (int d = dir; d <= dir + 1; d++) {
					dq2.push_back(cctvRegion(sX, sY, d));
				}
				dq2.push_back(cctvRegion(sX, sY, 4));
			}
			else if (dir == 4) {
				for (int d = dir - 1; d <= dir; d++) {
					dq2.push_back(cctvRegion(sX, sY, d));
				}
				dq2.push_back(cctvRegion(sX, sY, 1));
			}
			else {
				for (int d = dir - 1; d <= dir + 1; d++) {
					dq2.push_back(cctvRegion(sX, sY, d));
				}
			}
		}

	}
}

void set_dir(int idx) {
	if (idx == dq.size()) {
		copy_map();
		simulation();
		set_map();
		if (Answer == -1) Answer = copyEmptyCnt;
		else if (Answer > copyEmptyCnt) Answer = copyEmptyCnt;
		return;
	}

	int type = dq[idx].type;

	switch (type) {
	case 1:
		for (int i = 1; i <= 4; i++) {
			dq[idx].dir = i;
			set_dir(idx + 1);
		}
		break;
	case 2:
		for (int i = 1; i <= 2; i++) {
			dq[idx].dir = i;
			set_dir(idx + 1);
		}
		break;
	case 3:
		for (int i = 1; i <= 4; i++) {
			dq[idx].dir = i;
			set_dir(idx + 1);
		}
		break;
	case 4:
		for (int i = 1; i <= 4; i++) {
			dq[idx].dir = i;
			set_dir(idx + 1);
		}
		break;
	}
}

void Solution() {
	if (!dq2.empty()) set_origin_map();
	//print_info();
	
	set_dir(0);

	cout << Answer << endl;

}

void Input() {
	cctv tv(0, 0, 0, 0);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> originMap[i][j];
			if (originMap[i][j] > 0 && originMap[i][j] < 5) {
				tv.type = originMap[i][j], tv.xx = i, tv.yy = j, tv.dir = 0;
				dq.push_back(tv);
			}
			else if (originMap[i][j] == 5) {
				for (int k = 1; k <= 4; k++) {
					dq2.push_back(cctvRegion(i, j, k));
				}
			}
			else if (originMap[i][j] == 0) emptyCnt++;
			
		}
	}
}


int main(void) {
	Input();
	Solution();
	return 0;
}