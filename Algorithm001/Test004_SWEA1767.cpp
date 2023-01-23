#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <deque>
#include <vector>

using namespace std;

int N, Answer[2];
int map[13][13] = { 0, };

struct Core {
	int x, y, connectFlag, connectNum, connectCnt;
	Core(int x, int y, int connectFlag, int connectNum, int connectCnt) {
		this->x = x;
		this->y = y;
		this->connectFlag = connectFlag;
		this->connectNum = connectNum;
		this->connectCnt = connectCnt;
	}
};

deque <Core> dq;

int dx[5] = { 0, -1, 0, 1, 0 };
int dy[5] = { 0, 0, 1, 0, -1 };

void print_map() {
	cout << "맵" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void print_info() {
	cout << "코어 상태" << endl;
	for (int i = 0; i < dq.size(); i++) {
		cout << '(' << dq[i].x << ", " << dq[i].y << ") 위치에 코어 연결 상태: " << dq[i].connectFlag << ", 연결된 방향과 선 수: " << dq[i].connectNum << ", " << dq[i].connectCnt << endl;
	}
	cout << endl;
}

bool inRange(int x, int y) {
	if (x<1 || x>N || y < 1 || y > N) return false;
	return true;
}

void mask_map(int xx, int yy, int dir, int val) {
	int nX, nY;

	nX = xx, nY = yy;
	while (1) {
		nX = nX + dx[dir];
		nY = nY + dy[dir];
		if (!inRange(nX, nY)) break;
		map[nX][nY] = val;
	}

}

void core_connect(int cnt) {
	if (cnt == dq.size()) {
		int cnt = 0, num = 0;
		for (int i = 0; i < dq.size(); i++) {
			if (dq[i].connectFlag == 1) {
				cnt++;
				num = num + dq[i].connectCnt;
			}
		}

		if (Answer[0] < cnt) {
			Answer[0] = cnt;
			Answer[1] = num;
			//print_info();
			//print_map();
		}
		else if (Answer[0] == cnt && Answer[1] > num) {
			Answer[1] = num;
			//print_info();
			//print_map();
		}

		return;
	}

	int sX, sY, dir, tmpCnt, nX, nY, exitFlag = 0;
	sX = dq[cnt].x, sY = dq[cnt].y, exitFlag = dq[cnt].connectFlag;
	if (exitFlag == 1) {
		core_connect(cnt + 1);
		return;
	}

	for (dir = 1; dir <= 4; dir++) {
		nX = sX, nY = sY;
		exitFlag = 0;
		tmpCnt = 0;
		while (1) {
			nX = nX + dx[dir], nY = nY + dy[dir];
			if (map[nX][nY] == 0) {
				tmpCnt++;
				if (nX == 1 || nX == N || nY == 1 || nY == N) {
					dq[cnt].connectFlag = 1, dq[cnt].connectNum = dir, dq[cnt].connectCnt = tmpCnt;
					break;
				}
			}
			else {
				exitFlag = 1;
				break;
			}
		}
		if (exitFlag == 1) continue;

		mask_map(sX, sY, dir, 2);
		core_connect(cnt + 1);
		mask_map(sX, sY, dir, 0);
	}

	if (exitFlag == 1 && dq[cnt].connectFlag == 0) core_connect(cnt + 1);
	else {
		dq[cnt].connectFlag = 0, dq[cnt].connectNum = 0, dq[cnt].connectCnt = 0;
		core_connect(cnt + 1);
	}

}

void Solution() {
	Answer[0] = 0, Answer[1] = 0;
	core_connect(0);

	while (!dq.empty()) dq.pop_back();
}

void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) {
				dq.push_back({ i, j, 0, 0, 0 });
				if (i == 1 || i == N || j == 1 || j == N) dq[dq.size() - 1].connectFlag = 1;
			}
		}
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	//freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		Input();
		Solution();
		cout << '#' << test_case << ' ' << Answer[1] << '\n';
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}