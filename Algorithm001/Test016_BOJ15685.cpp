/*
�巡�� Ŀ��� ������ ���� �� ���� �Ӽ����� �̷���� ������, ������ ��ǥ ��� ������ ���ǵȴ�.
��ǥ ����� x���� �� ����, y���� �� �����̴�.

1.���� ��
2. ���� ����
3. ����
0���� �巡�� Ŀ��� �Ʒ� �׸��� ���� ���̰� 1�� �����̴�. �Ʒ� �׸��� (0, 0)���� �����ϰ�,
���� ������ �������� 0���� �巡�� Ŀ���̴�.

1���� �巡�� Ŀ��� 0���� �巡�� Ŀ�긦 �� ���� �������� �ð� �������� 90�� ȸ����Ų ����
0���� �巡�� Ŀ���� �� ���� ���� ���̴�. �� ���̶� ���� ������ ������ Ÿ�� �̵����� ��, ���� �� �Ÿ��� �ִ� ���� �ǹ��Ѵ�.

2���� �巡�� Ŀ�굵 1���븦 ���� ����� �̿��ؼ� ���� �� �ִ�. (�Ķ��� ������ ���� �߰��� ������ ��Ÿ����)

3���� �巡�� Ŀ�굵 2���� �巡�� Ŀ�긦 �̿��� ���� �� �ִ�. �Ʒ� �׸��� 3���� �巡�� Ŀ���̴�.

��, K(K > 1)���� �巡�� Ŀ��� K-1���� �巡�� Ŀ�긦 �� ���� �������� 90�� �ð� ���� ȸ�� ��Ų ����,
�װ��� �� ���� ���� ���̴�.

ũ�Ⱑ 100��100�� ���� ���� �巡�� Ŀ�갡 N�� �ִ�.
�̶�, ũ�Ⱑ 1��1�� ���簢���� �� �������� ��� �巡�� Ŀ���� �Ϻ��� ���簢���� ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
������ ��ǥ�� (x, y)�� ��Ÿ����, 0 �� x �� 100, 0 �� y �� 100�� ��ȿ�� ��ǥ�̴�.

�Է�
ù° �ٿ� �巡�� Ŀ���� ���� N(1 �� N �� 20)�� �־�����. ��° �ٺ��� N���� �ٿ��� �巡�� Ŀ���� ������ �־�����.
�巡�� Ŀ���� ������ �� ���� x, y, d, g�� �̷���� �ִ�. x�� y�� �巡�� Ŀ���� ���� ��, d�� ���� ����, g�� �����̴�.
(0 �� x, y �� 100, 0 �� d �� 3, 0 �� g �� 10)
�Է����� �־����� �巡�� Ŀ��� ���� ������ ����� �ʴ´�. �巡�� Ŀ��� ���� ��ĥ �� �ִ�.
������ 0, 1, 2, 3 �� �ϳ��̰�, ������ �ǹ��Ѵ�.
0: x��ǥ�� �����ϴ� ���� (��)
1: y��ǥ�� �����ϴ� ���� (��)
2: x��ǥ�� �����ϴ� ���� (��)
3: y��ǥ�� �����ϴ� ���� (��)

���
ù° �ٿ� ũ�Ⱑ 1��1�� ���簢���� �� �������� ��� �巡�� Ŀ���� �Ϻ��� ���� ������ ����Ѵ�.

N, dragon[21][4], deque <int> dq, dx[4], dy[4], map[101][101];

1. Input()
	N, dragon
2. Solution()
	1) find_curve()
		1-1) for(int idx=0; idx <N; idx++)
		1-2) find_curve(int startX, int startY, int curG, int nextG)�� �巡�� Ŀ�� ���� ���ϱ�
		1-3) �� idx���� dq�� ������ �� ���� ����
		1-4) curG==nextG��, map�� ǥ��
	2) find_answer()
		2-1) �� �������� �巡�� Ŀ���� �簢�� ã��
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, Answer = 0;
int dragon[21][4];

deque <int> dq;
int map[101][101] = { 0, };
int dx[4] = { 0, -1, 0, 1 };
int dy[4] = { 1, 0, -1, 0 };

void print_map() {
	cout << "map" << endl;
	for (int i = 0; i <= 100; i++) {
		for (int j = 0; j <= 100; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void find_answer() {
	for (int i = 0; i <= 100; i++) {
		for (int j = 0; j <= 100; j++) {
			if (i + 1 > 100 || j + 1 > 100) continue;
			if (map[i][j] > 0 && map[i + 1][j] > 0 && map[i][j + 1] > 0 && map[i + 1][j + 1] > 0) {
				Answer++;
			}
		}
	}
}

void find_curve(int idx, int startX, int startY, int curG, int nextG) {
	if (curG == nextG) {
		int nextX, nextY, dir;

		map[startX][startY] = 1;
		nextX = startX;
		nextY = startY;
		while (!dq.empty()) {
			dir = dq.front();
			nextX = nextX + dx[dir];
			nextY = nextY + dy[dir];
			if (nextX >= 0 && nextX <= 100 && nextY >= 0 && nextY <= 100) {
				map[nextX][nextY] = idx;
			}

			dq.pop_front();
		}

		return;
	}

	int dSize = dq.size() - 1;

	int curD, nextD;
	for (int i = dSize; i >= 0; i--) {
		curD = dq[i];
		nextD = curD + 1;
		if (nextD > 3) nextD = 0;
		dq.push_back(nextD);
	}

	find_curve(idx, startX, startY, curG + 1, nextG);
}

void Solution() {
	for (int idx = 0; idx < N; idx++) {
		dq.push_back(dragon[idx][2]);
		find_curve(idx + 1, dragon[idx][0], dragon[idx][1], 0, dragon[idx][3]);
	}

	//print_map();
	find_answer();
}

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> dragon[i][1] >> dragon[i][0] >> dragon[i][2] >> dragon[i][3];
	}
}

int main(void) {
	Input();
	Solution();

	cout << Answer << endl;
	return 0;
}