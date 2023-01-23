/*
�̼������� �����ϱ� ���� ������� ����û���⸦ ��ġ�Ϸ��� �Ѵ�.
����û������ ������ �׽�Ʈ�ϱ� ���� ������� ���� ũ�Ⱑ R��C�� ���������� ��Ÿ�°�, 1��1 ũ���� ĭ���� ������.
������� �پ �ڵ� �Ƿ��� �̿��� �� ĭ (r, c)�� �ִ� �̼������� ���� �ǽð����� ����͸��ϴ� �ý����� �����ߴ�.
(r, c)�� r�� c���� �ǹ��Ѵ�.

����û����� �׻� 1�� ���� ��ġ�Ǿ� �ְ�, ũ��� �� ���� �����Ѵ�. ����û���Ⱑ ��ġ�Ǿ� ���� ���� ĭ���� �̼������� �ְ�,
(r, c)�� �ִ� �̼������� ���� Ar,c�̴�.

1�� ���� �Ʒ� ���� ���� ������� �Ͼ��.

1. �̼������� Ȯ��ȴ�. Ȯ���� �̼������� �ִ� ��� ĭ���� ���ÿ� �Ͼ��.
	(r, c)�� �ִ� �̼������� ������ �� �������� Ȯ��ȴ�.
	������ ���⿡ ����û���Ⱑ �ְų�, ĭ�� ������ �� �������δ� Ȯ���� �Ͼ�� �ʴ´�.
	Ȯ��Ǵ� ���� Ar,c/5�̰� �Ҽ����� ������.
	(r, c)�� ���� �̼������� ���� Ar,c - (Ar,c/5)��(Ȯ��� ������ ����) �̴�.

2. ����û���Ⱑ �۵��Ѵ�.
	����û���⿡���� �ٶ��� ���´�.
	���� ����û������ �ٶ��� �ݽð�������� ��ȯ�ϰ�, �Ʒ��� ����û������ �ٶ��� �ð�������� ��ȯ�Ѵ�.
	�ٶ��� �Ҹ� �̼������� �ٶ��� ������ ��� �� ĭ�� �̵��Ѵ�.
	����û���⿡�� �δ� �ٶ��� �̼������� ���� �ٶ��̰�, ����û����� �� �̼������� ��� ��ȭ�ȴ�.

����û������ �ٶ��� ������ ���� �������� ��ȯ�Ѵ�.
���� ������ �־����� ��, T�ʰ� ���� �� ������� �濡 �����ִ� �̼������� ���� ���غ���.

�Է�
ù° �ٿ� R, C, T (6 �� R, C �� 50, 1 �� T �� 1,000) �� �־�����.
��° �ٺ��� R���� �ٿ� Ar,c (-1 �� Ar,c �� 1,000)�� �־�����. ����û���Ⱑ ��ġ�� ���� Ar,c�� -1�̰�,
������ ���� �̼������� ���̴�. -1�� 2�� ���Ʒ��� �پ��� �ְ�, ���� �� ��, �Ʒ� ��� �� ĭ�̻� ������ �ִ�.

���
ù° �ٿ� T�ʰ� ���� �� ����� �濡 �����ִ� �̼������� ���� ����Ѵ�.

R, C, T, map[51][51], int airCondi[2][2];
deque <pair <int, pair<int, int>>> add;

1. Input()
	R, C, T, map[R][C], dq, airCondi[2][2];

2. Solution() ; 0~T��ŭ 1~2 �ݺ�
	1) spread_air()
		1-1) for(int xx=0; xx<R; xx++), for(int yy=0; yy<C; yy++)
		1-2) map[xx][yy] >= 5�̸�, Ȯ�� ����
		1-3) d=0~4���� Ȯ���� �� �ִ� �̼����� ã�� & cnt�� ����
		1-4) add�� Ȯ���ϴ� �̼����� ũ��, x, y ����
		1-5) map[x][y]/5 * cnt��ŭ map[x][y]�� ����
		1-6) 1-1~5) ���� �ݺ��ؼ� ���� add ���鼭 map�� ����
	2) oprate_airCondi()
		2-1) ��û�� �����ϴ� �� ����
	3) find_answer()
		3-1) for(int xx=0; xx<R; xx++), for(int yy=0; yy<C; yy++) Ž���ϸ鼭 �̼����� ���� ���ϱ�
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int R, C, T, Answer = 0;
int map[51][51] = { 0, }, airCondi[2][2];

deque <pair <int, pair<int, int>>> add;

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void print_map() {
	cout << "map" << endl;
	for (int xx = 0; xx < R; xx++) {
		for (int yy = 0; yy < C; yy++) {
			cout << map[xx][yy] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void spread_air() {
	int cnt, airSize, nX, nY;

	for (int xx = 0; xx < R; xx++) {
		for (int yy = 0; yy < C; yy++) {
			if (map[xx][yy] >= 5) {
				cnt = 0;
				airSize = map[xx][yy] / 5;

				for (int d = 0; d < 4; d++) {
					nX = xx + dx[d];
					nY = yy + dy[d];
					if (nX < 0 || nX >= R || nY < 0 || nY >= C) continue;
					if (map[nX][nY] == -1) continue;

					add.push_back(make_pair(airSize, make_pair(nX, nY)));
					cnt++;
				}

				map[xx][yy] = map[xx][yy] - (cnt * airSize);
			}
		}
	}

	while (!add.empty()) {
		map[add.front().second.first][add.front().second.second] = map[add.front().second.first][add.front().second.second] + add.front().first;
		add.pop_front();
	}
}

void oprate_airCondi() {
	int sX, sY, nX, nY, xx, yy;

	queue <int> q;

	sX = airCondi[0][0];
	sY = airCondi[0][1];
	
	q.push(map[sX][sY + 1]);
	map[sX][sY + 1] = 0;
	xx = sX;
	for (yy = sY + 2; yy < C; yy++) {
		q.push(map[xx][yy]);
		map[xx][yy] = q.front();
		q.pop();
	}
	yy = C - 1;
	for (xx = sX - 1; xx >= 0; xx--) {
		q.push(map[xx][yy]);
		map[xx][yy] = q.front();
		q.pop();
	}
	xx = 0;
	for (yy = C - 2; yy >= 0; yy--) {
		q.push(map[xx][yy]);
		map[xx][yy] = q.front();
		q.pop();
	}
	yy = sY;
	for (xx = 1; xx < sX; xx++) {
		q.push(map[xx][yy]);
		map[xx][yy] = q.front();
		q.pop();
	}
	q.pop();

	sX = airCondi[1][0];
	sY = airCondi[1][1];

	q.push(map[sX][sY + 1]);
	map[sX][sY + 1] = 0;
	xx = sX;
	for (yy = sY + 2; yy < C; yy++) {
		q.push(map[xx][yy]);
		map[xx][yy] = q.front();
		q.pop();
	}
	yy = C - 1;
	for (xx = sX + 1; xx < R; xx++) {
		q.push(map[xx][yy]);
		map[xx][yy] = q.front();
		q.pop();
	}
	xx = R - 1;
	for (yy = C - 2; yy >= 0; yy--) {
		q.push(map[xx][yy]);
		map[xx][yy] = q.front();
		q.pop();
	}
	yy = sY;
	for (xx = R - 2; xx > sX; xx--) {
		q.push(map[xx][yy]);
		map[xx][yy] = q.front();
		q.pop();
	}
	q.pop();
}

void find_answer() {
	Answer = 0;
	
	for (int xx = 0; xx < R; xx++) {
		for (int yy = 0; yy < C; yy++) {
			if (map[xx][yy] > 0) Answer = Answer + map[xx][yy];
		}
	}
}

void Solution() {
	for (int time = 0; time < T; time++) {
		spread_air();
		oprate_airCondi();
	}
	find_answer();
	cout << Answer << endl;
}

void Input() {
	int idx = 0;
	cin >> R >> C >> T;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
			if (map[i][j] == -1) {
				airCondi[idx][0] = i;
				airCondi[idx][1] = j;
				idx++;
			}
		}
	}
}

int main(void) {
	Input();
	Solution();
	//spread_air();
	//print_map();
	//oprate_airCondi();
	//print_map();
	return 0;
}