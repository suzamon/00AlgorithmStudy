/*
�߽ó뽺�� ���� N�� x ���� N���� cell�� ����

1���� cell���� 1���� Core Ȥ�� 1���� ����
�߽ó뽺�� ���� �ڸ����� ����
Core�� ������ �����ϴ� ������ �������θ� ��ġ�� ����
������ ����� �����ؼ��� �� �ȴ�
�ʱ� ���·δ� �Ʒ��� ���� ������ �����ϱ� �� ������ �߽ó뽺 ����
(�߽ó뽺�� �����ڸ��� ��ġ�� Core�� �̹� ������ ����� ������ �����Ѵ�.)
�� �ִ��� ���� Core�� ������ �����Ͽ��� ���, ���� ������ ��
 ��, ���� ����� ���� ���, ���� ������ ���� �ּҰ� �Ǵ� ��

1. 7 ��  N �� 12
2. Core�� ������ �ּ� 1�� �̻� 12�� �����̴�.
3. �ִ��� ���� Core�� ������ �����ص�, ������ ������� �ʴ� Core�� ������ �� �ִ�.

T, NxN��, Core = 1


1. Input() : T, map[N][N], Core[12][2], dx[5], dy[5](��, ��, �� ��), coreCnt, connectCnt, Answer
connectPos[12][5] -> Core�� ���� ������ �𼭸� ��ġ ����, �� ������ ��ġ(0(��), 1(��), 2(��), 3(��))
[0] ���� -1�̸� �̹� ����, 0�̸� ���� �Ұ�

2. Solution() :
	1. find_Pos()
		: �� �ھ ���� ������ �𼭸� ã�� -> ������ ���� [0]�� ���� & ������ ��ġ ����
	2. set_elec(int start, int cnt, int )
		: connectPos���� ������ ��ġ ���� �� ���� Core
		: start == coreCnt��, ����� cnt�� CoonectCnt �� �� ���ų� ũ�� ���� min ��
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
	cout << "��ġ: 1(��), 2(��), 3(��), 4(��)" << endl;
	for (int i = 0; i < coreCnt; i++) {
		cout << i << "��° core  ��ġ: (" << core[i][0] << ", " << core[i][1] <<')'<< endl;
	    cout<<"���� ������ ��ġ ����: " << connectPos[i][0];
		cout <<", �� ��ġ: ";
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
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}