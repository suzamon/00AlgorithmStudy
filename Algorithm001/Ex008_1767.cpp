/*
멕시노스는 가로 N개 x 세로 N개의 cell로 구성

1개의 cell에는 1개의 Core 혹은 1개의 전선
멕시노스의 가장 자리에는 전원
Core와 전원을 연결하는 전선은 직선으로만 설치가 가능
전선은 절대로 교차해서는 안 된다
초기 상태로는 아래와 같이 전선을 연결하기 전 상태의 멕시노스 정보
(멕시노스의 가장자리에 위치한 Core는 이미 전원이 연결된 것으로 간주한다.)
▶ 최대한 많은 Core에 전원을 연결하였을 경우, 전선 길이의 합
 단, 여러 방법이 있을 경우, 전선 길이의 합이 최소가 되는 값

1. 7 ≤  N ≤ 12
2. Core의 개수는 최소 1개 이상 12개 이하이다.
3. 최대한 많은 Core에 전원을 연결해도, 전원이 연결되지 않는 Core가 존재할 수 있다.

T, NxN개, Core = 1


1. Input() : T, map[N][N], Core[12][2], dx[5], dy[5](상, 우, 하 좌), coreCnt, connectCnt, Answer
connectPos[12][5] -> Core별 연결 가능한 모서리 위치 갯수, 각 가능한 위치(0(상), 1(우), 2(하), 3(좌))
[0] 값이 -1이면 이미 연결, 0이면 연결 불가

2. Solution() :
	1. find_Pos()
		: 각 코어별 연결 가능한 모서리 찾기 -> 가능한 갯수 [0]에 저장 & 가능한 위치 저장
	2. set_elec(int start, int cnt, int )
		: connectPos에서 가능한 위치 연결 후 다음 Core
		: start == coreCnt면, 연결된 cnt와 CoonectCnt 비교 후 같거나 크면 전선 min 값
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>

using namespace std;

int T, N, coreCnt, connectCnt, Answer;
int map[13][13];
int core[12][2];
int connectPos[12][5];

int dx[5] = { 0, -1, 0, 1, 0 };
int dy[5] = { 0, 0, 1, 0, -1 };

void print_map() {
	cout << "map" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void Input() {
	coreCnt = 0, connectCnt = 0, Answer = 99999;
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) {
				core[coreCnt][0] = i;
				core[coreCnt][1] = j;
				coreCnt++;
			}
		}
	}
}

void print_pos() {
	cout << "위치: 1(상), 2(우), 3(하), 4(좌)" << endl;
	for (int i = 0; i < coreCnt; i++) {
		cout << i << "번째 core  위치: (" << core[i][0] << ", " << core[i][1] <<')'<< endl;
	    cout<<"연결 가능한 위치 갯수: " << connectPos[i][0];
		cout <<", 각 위치: ";
		for (int j = 1; j <= connectPos[i][0]; j++) {
			cout << connectPos[i][j] << ' ';
		}
		cout << endl;
		cout << endl;
	}
	cout << endl;
}


bool inRange(int nextX, int nextY) {
	if (nextX >= 0 && nextX < N && nextY >= 0 && nextY < N) return true;
	else return false;
}

void find_pos() {
	int startX, startY, nextX, nextY, cnt;
	for (int i = 0; i < coreCnt; i++) {
		cnt = 0;
		startX = core[i][0];
		startY = core[i][1];
		if (startX == 0 || startX == N - 1 || startY == 0 || startY == N - 1) {
			connectPos[i][0] = -1;
			continue;
		}

		for (int d = 1; d <= 4; d++) {
			nextX = startX;
			nextY = startY;
			while (1) {
				nextX = nextX + dx[d];
				nextY = nextY + dy[d];
				if (!inRange(nextX, nextY)) {
					cnt++;
					connectPos[i][cnt] = d;
					break;
				}
				else if (map[nextX][nextY] == 1) break;

			}
		}
		connectPos[i][0] = cnt;
	}
}

int map_sim(int startX, int startY, int dir) {
	int ret = 0, nextX, nextY;

	nextX = startX, nextY = startY;
	while (1) {
		nextX = nextX + dx[dir];
		nextY = nextY + dy[dir];
		if (!inRange(nextX, nextY)) break;
		else if (map[nextX][nextY] != 0) {
			ret = -1;
			break;
		}
	}
	return ret;
}

int set_map(int startX, int startY, int dir, int digit) {
	int nextX, nextY;

	int elecCnt = 0;
	nextX = startX, nextY = startY;
	while (1) {
		nextX = nextX + dx[dir];
		nextY = nextY + dy[dir];
		if (!inRange(nextX, nextY)) break;
		map[nextX][nextY] = digit;
		elecCnt++;
		
	}
	return elecCnt;
}

void connect_sim(int idx, int cnt, int elecCnt) {
	if (idx == coreCnt) {
		//print_map();
		if (cnt > connectCnt) {
			connectCnt = cnt;
			Answer = elecCnt;
		}
		else if (cnt == connectCnt) {
			Answer = min(Answer, elecCnt);
		}
		return;
	}

	if (connectPos[idx][0] == -1) {
		connect_sim(idx + 1, cnt + 1, elecCnt);
		return;
	}
	else if (connectPos[idx][0] == 0) {
		connect_sim(idx + 1, cnt, elecCnt);
		return;
	}

	int nextElecCnt, flag = 0;
	for (int i = 1; i <= connectPos[idx][0]; i++) {
		flag = map_sim(core[idx][0], core[idx][1], connectPos[idx][i]);
		if (flag != -1) {
			nextElecCnt = set_map(core[idx][0], core[idx][1], connectPos[idx][i], 2);
			connect_sim(idx + 1, cnt + 1, elecCnt + nextElecCnt);
			nextElecCnt = set_map(core[idx][0], core[idx][1], connectPos[idx][i], 0);
		}
		else {
			connect_sim(idx + 1, cnt, elecCnt);
		}
	}

}

void Solution() {
	find_pos();

	connect_sim(0, 0, 0);

}


int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		Input();
		Solution();
		cout << '#' << test_case << ' ' <<Answer<< endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}