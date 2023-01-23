/*
������ �̷���� ���� �ְ�, ��� ���� �ٸ��� �����Ϸ��� �Ѵ�.
�� ������ ������ N��M ũ���� ������ ���ڷ� ��Ÿ�� �� �ְ�, ������ �� ĭ�� ���̰ų� �ٴ�
���� ����� ���� �����¿�� �پ��ִ� ���
�ٸ��� �ٴٿ��� �Ǽ��� �� �ְ�, �ٸ��� ���̴� �ٸ��� ���ڿ��� �����ϴ� ĭ�� ��
�ٸ��� �����ؼ� ��� ���� �����Ϸ��� �Ѵ�. �� A���� �ٸ��� ���� �� B�� �� �� ���� ��, �� A�� B�� ����Ǿ���
�ٸ��� �� ���� ���� ������ �ٴ� ���� �־�� �ϰ�, �� �ٸ��� ������ �߰��� �ٲ�� �ȵȴ�.
�ٸ��� ���̴� 2 �̻��̾�� �Ѵ�.

�ٸ��� ������ �߰��� �ٲ�� �ȵǱ� ������,
�ٸ��� ������ ���� �Ǵ� ����
-> ������ ������ �ٸ��� �ٸ��� �� ���� ���� �������� ���� ����
-> ������ ������ �ٸ��� �ٸ��� �� ���� ���� �������� ���� ����
�� A�� B�� �����ϴ� �ٸ��� �߰��� �� C�� ������ �ٴٸ� �������� ��쿡 �� C�� A, B�� ����Ǿ��ִ� ���� �ƴϴ�.
�ٸ��� �����ϴ� ��찡 ���� ���� �ִ�. �����ϴ� �ٸ��� ���̸� ����� ���� �� ĭ�� �� �ٸ��� ���̿� ��� ����

Answer : ��� ���� �����ϴ� �ٸ� ������ �ּڰ��� ����Ѵ�. ��� ���� �����ϴ� ���� �Ұ����ϸ� -1�� ���

ù° �ٿ� ������ ���� ũ�� N�� ���� ũ�� M
��° �ٺ��� N���� �ٿ� ������ ������ �־�����.
�� ���� M���� ���� �̷���� ������, ���� 0 �Ǵ� 1�̴�. 0�� �ٴ�, 1�� ���� �ǹ�

1 �� N, M �� 10
3 �� N��M �� 100
2 �� ���� ���� �� 6

��� ���� -> N-1 ���� �ٸ�

1. Input() : map[N][M], visited[N][M], islandCnt, connectMap[6][6], deque <int, int> island[6] -> �� ���� ���� ��, ������ �Ʒ� ��ġ ����


2. Solution():
	1) check_island()
		: BFS�� �� �� ���� Ž�� & �ʿ� 1~6���� ǥ�� & islandCnt�� �� ���� ����
		: islandCnt, map�� ǥ��, connectMap �ʱ�ȭ, deque island�� idx�� �� ��ġ ���� ����
	2) find_connect_island(int startIdx) -> possible[6][6][4] =>
		: �ʿ��� ���� ->
		 possible[startIdx][endIdx][0] (�ٸ� ���� ���� ���ɼ� 0: �Ұ�, 1: ����),
		 possible[startIdx][endIdx][1] -> �ּ� �ٸ� ����,
		 possible[startIdx][endIdx][2][3] -> ������ ��, row, col ��
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

deque <pair <int, int>> island[7]; //�� idx�� ��ǥ ����
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
		cout << i << "�� �� ũ��: " << island[i].size() << endl;
		for (int j = 1; j <= islandCnt; j++) {
			cout << j << "�� ���� ���� ���ɼ�: " << possible[i][j][0] << endl;
			if (possible[i][j][0] == 1) {
				cout << "�ּ� �ٸ� ����: " << possible[i][j][1] << ", ���� ����Ʈ: (" << possible[i][j][2] << ", " << possible[i][j][3] << ')' << endl;
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
				else { //�ٸ� �� ������ ��
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