/*
ũ�Ⱑ N��M�� ����, ������ �������� ����, ������ ����
���� ��ǥ�� (r, c)�� ��Ÿ����, r�� �������κ��� ������ ĭ�� ����, c�� �������κ��� ������ ĭ�� ����
�ֻ����� ���� ���� �� ���� 1�̰�, ������ �ٶ󺸴� ������ 3�� ���·� ������ ������, ������ �ִ� ���� ��ǥ�� (x, y) �̴�.
���� ó���� �ֻ������� ��� �鿡 0�� ������ �ִ�.

������ �� ĭ���� ������ �ϳ��� ������ �ִ�.
�ֻ����� ������ ��, �̵��� ĭ�� ���� �ִ� ���� 0�̸�, �ֻ����� �ٴڸ鿡 ���� �ִ� ���� ĭ�� ����,
0�� �ƴ� ��쿡�� ĭ�� ���� �ִ� ���� �ֻ����� �ٴڸ����� ����Ǹ�, ĭ�� ���� �ִ� ���� 0�� �ȴ�.

�ֻ����� ���� ���� ��ǥ�� �̵���Ű�� ����� �־����� ��,
�ֻ����� �̵����� �� ���� ��ܿ� ���� �ִ� ���� ���ϴ� ���α׷��� �ۼ�

�ֻ����� ������ �ٱ����� �̵���ų �� ����.
���� �ٱ����� �̵���Ű���� �ϴ� ��쿡�� �ش� ����� �����ؾ� �ϸ�, ��µ� �ϸ� �� �ȴ�.

ù° �ٿ� ������ ���� ũ�� N, ���� ũ�� M (1 �� N, M �� 20),
�ֻ����� ���� ���� ��ǥ x, y(0 �� x �� N-1, 0 �� y �� M-1), �׸��� ����� ���� K (1 �� K �� 1,000)�� �־�����.

��° �ٺ��� N���� �ٿ� ������ ���� �ִ� ���� ���ʺ��� ��������,
�� ���� ���ʺ��� ���� ������� �־�����. �ֻ����� ���� ĭ�� ���� �ִ� ���� �׻� 0�̴�.
������ �� ĭ�� ���� �ִ� ���� 10 �̸��� �ڿ��� �Ǵ� 0�̴�.

������ �ٿ��� �̵��ϴ� ����� ������� �־�����. ������ 1, ������ 2, ������ 3, ������ 4�� �־�����.

�̵��� ������ �ֻ����� �� �鿡 ���� �ִ� ���� ����Ѵ�.
���� �ٱ����� �̵���Ű���� �ϴ� ��쿡�� �ش� ����� �����ؾ� �ϸ�, ��µ� �ϸ� �� �ȴ�.

<dice Map> => �̵��� ������ 6�� ��� & 1�� ��ġ �� ����
0 2 0
4 1 3
0 5 0
0 6 0

1) ��
0 2 0
1 3 6
0 5 0
0 4 0

2) ��
0 2 0
6 4 1
0 5 0
0 3 0

3) ��
0 6 0
4 2 3
0 1 0
0 5 0

4) ��
0 1 0
4 5 3
0 6 0
0 2 0

�̵� -> deque�� ����

1. Input
	N, M, dice[2], K
	Map[N][M]
	command[K]

2. Solution
	1. 1~K��ŭ ����
	2) ���� dice x,y �̵� -> �� ���̸� ����X
	3-1-1) �̵� ��ɾ ��ȿ�ϸ� dice �� ����
	3-1-2) map[diceX][diceY] == 0�̸� dice �� ����, �ƴϸ� map �� ���� & ������Ʈ
	3-2) �̵� ��ɾ� ��ȿ -> �״��
	4) diceMap[3][2] ���
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, M, K, Answer = 0;

int dice[2], diceMap[4][3] = { 0, };
//int diceMap[4][3] = { {0, 2, 0}, {4, 1, 3}, {0, 5, 0}, {0, 6, 0} };
int map[21][21];
int command[1001];


int dx[5] = { 0, 0, 0, -1, 1 };
int dy[5] = { 0, 1, -1, 0, 0 };

void print_dice() {
	cout << "Dice Map" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			cout << diceMap[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void move_dice(int dir) {
	deque <int> dq;

	switch (dir) {
	case 1:
		for (int i = 0; i < 3; i++) dq.push_back(diceMap[1][i]);
		dq.push_back(diceMap[3][1]);

		diceMap[3][1] = dq.front();
		dq.pop_front();
		for (int i = 0; i < 3; i++) {
			diceMap[1][i] = dq.front();
			dq.pop_front();
		}
		break;
	case 2:
		dq.push_back(diceMap[3][1]);
		for (int i = 0; i < 3; i++) dq.push_back(diceMap[1][i]);
		
		for (int i = 0; i < 3; i++) {
			diceMap[1][i] = dq.front();
			dq.pop_front();
		}
		diceMap[3][1] = dq.front();
		dq.pop_front();
		break;
	case 3:
		for (int i = 0; i < 4; i++) dq.push_back(diceMap[i][1]);

		for (int i = 1; i < 4; i++) {
			diceMap[i][1] = dq.front();
			dq.pop_front();
		}
		diceMap[0][1] = dq.front();
		dq.pop_front();
		break;
	case 4:
		for (int i = 0; i < 4; i++) dq.push_back(diceMap[i][1]);

		diceMap[3][1] = dq.front();
		dq.pop_front();
		for (int i = 0; i < 3; i++) {
			diceMap[i][1] = dq.front();
			dq.pop_front();
		}
		break;
	}
}

void Solution() {
	int idx, nextX, nextY;

	for (idx = 0; idx < K; idx++) {
		nextX = dice[0] + dx[command[idx]];
		nextY = dice[1] + dy[command[idx]];

		if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) continue;

		dice[0] = nextX;
		dice[1] = nextY;

		move_dice(command[idx]);
		if (map[dice[0]][dice[1]] == 0) {
			map[dice[0]][dice[1]] = diceMap[1][1];
		}
		else {
			diceMap[1][1] = map[dice[0]][dice[1]];
			map[dice[0]][dice[1]] = 0;
		}

		
		//print_dice();
		cout << diceMap[3][1] << endl;
	}
}

void Input() {
	cin >> N >> M >> dice[0] >> dice[1] >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < K; i++) {
		cin >> command[i];
	}
}

int main(void) {
	Input();
	Solution();

	//move_dice(4);
	//print_dice();

	return 0;
}