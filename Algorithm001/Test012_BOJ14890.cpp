/*
ũ�Ⱑ N��N�� ������ �ִ�. ������ �� ĭ���� �� ���� ���̰� ������ �ִ�.

������ �� �������� ������ �� �ִ� ���� �� �� �ִ��� �˾ƺ����� �Ѵ�.
���̶� �� �� �Ǵ� �� �� ���θ� ��Ÿ����, ���� ������ �ٸ��� ������ �������� ���̴�.

������ ���� N=6�� ��� ������ ���캸��.

�̶�, ���� �� 2N���� ������, �Ʒ��� ����.

���� ������ �� �������� �濡 ���� ��� ĭ�� ���̰� ��� ���ƾ� �Ѵ�. �Ǵ�, ���θ� ���Ƽ� ������ �� �ִ� ���� ���� �� �ִ�
���δ� ���̰� �׻� 1�̸�, ���̴� L�̴�. ��, ������ �ſ� ���� ������ ���� ����.
���δ� ���� ĭ�� ���� ĭ�� �����ϸ�, �Ʒ��� ���� ������ �����ؾ��Ѵ�.

���δ� ���� ĭ�� ������, L���� ���ӵ� ĭ�� ������ �ٴ��� ��� ���ؾ� �Ѵ�.
���� ĭ�� ���� ĭ�� ���� ���̴� 1�̾�� �Ѵ�.
���θ� ���� ���� ĭ�� ���̴� ��� ���ƾ� �ϰ�, L���� ĭ�� ���ӵǾ� �־�� �Ѵ�.

�Ʒ��� ���� ��쿡�� ���θ� ���� �� ����.

���θ� ���� ���� �� ���θ� ���� ���
���� ĭ�� ���� ĭ�� ���� ���̰� 1�� �ƴ� ���
���� ������ ĭ�� ���̰� ��� ���� �ʰų�, L���� ���ӵ��� ���� ���
���θ� ���ٰ� ������ ����� ���

���� ���� �־��� �׸� ���� ��쿡 ������ �� �ִ� ���� �Ķ�������, ������ �� ���� ���� ���������� ǥ�õǾ� ������,
�Ʒ��� ����. ������ ���� L = 2�̴�.

������ �־����� ��, ������ �� �ִ� ���� ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

�Է�
ù° �ٿ� N (2 �� N �� 100)�� L (1 �� L �� N)�� �־�����. ��° �ٺ��� N���� �ٿ� ������ �־�����.
�� ĭ�� ���̴� 10���� �۰ų� ���� �ڿ����̴�.

���
ù° �ٿ� ������ �� �ִ� ���� ������ ����Ѵ�.


1. Input()
	N, L, map[N][N][2], rotMap[N][N][2]

2. Solution() -> map�� rotMap �Ѵ� ����
	1) �� �ึ�� ����
	2) ���������� Ž��(0~N-1���� ����) -> �� �� ��
	3) curH, nextH ���� ��
		3-1) 0�̸� ����ĭ �ٷ� ����
		3-2) 0�� �ƴϸ�, curH�� nextH ũ�� ��
			3-2-1) curH > nextH��, nextH <= col < nextH + L����
					 map[row][col][1] == 0 && map[row][nextH][0] == map[row][col][0]�� �´��� ��
					-> ���� �����ϸ� [1]�� ����, �Ҹ����̸� 0 ��ȯ
					-> �������� �����ϸ� ���� curH = nextH + L -1���� ����
			3-2-2) curH < nextH��, curH - L < col <= curH ����
					 map[row][col][1] == 0 && map[row][curH][0] == map[row][col][0]�� �´��� ��
					-> ���� �����ϸ� [1]�� ����, �Ҹ����̸� 0 ��ȯ
					-> �������� �����ϸ� ���� curH = nextH���� ����
	4) ������ Ž�� �Ϸ��ϸ� 1 ��ȯ
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, L, Answer = 0;
int map[101][101][2], rotMap[101][101][2];

int check_rot_row(int row) {
	int ret = 1, curH, nextH;

	for (int i = 0; i < N - 1; i++) {
		curH = rotMap[row][i][0];
		nextH = rotMap[row][i + 1][0];
		if (curH == nextH) continue;
		else if (curH - nextH == 1) {
			if (i + L >= N) return 0;
			for (int col = i + 1; col <= i + L; col++) {
				if (rotMap[row][col][1] == 0 && rotMap[row][col][0] == nextH) {
					rotMap[row][col][1] = 1;
				}
				else return 0;
			}
			i = i + L - 1;
		}
		else if (nextH - curH == 1) {
			if (i - L + 1 < 0) return 0;
			for (int col = i; col > i - L; col--) {
				if (rotMap[row][col][1] == 0 && rotMap[row][col][0] == curH) {
					rotMap[row][col][1] = 1;
				}
				else return 0;
			}
		}
		else return 0;
	}

	return 1;
}

int check_row(int row) {
	int ret = 1, curH, nextH;

	for (int i = 0; i < N - 1; i++) {
		curH = map[row][i][0];
		nextH = map[row][i + 1][0];
		if (curH == nextH) continue;
		else if (curH - nextH == 1) {
			if (i + L >= N) return 0;
			for (int col = i + 1; col <= i + L; col++) {
				if (map[row][col][1] == 0 && map[row][col][0] == nextH) {
					map[row][col][1] = 1;
				}
				else return 0;
			}
			i = i + L - 1;
		}
		else if (nextH - curH == 1) {
			if (i - L + 1 < 0) return 0;
			for (int col = i; col > i - L; col--) {
				if (map[row][col][1] == 0 && map[row][col][0] == curH) {
					map[row][col][1] = 1;
				}
				else return 0;
			}
		}
		else return 0;
	}

	return 1;
}

void Solution() {
	Answer = 0;

	//cout << "���� �� ��" << endl;
	for (int row = 0; row < N; row++) {
		if (check_row(row) == 1) {
			//cout << row + 1 << "�� ���� ����" << endl;
			Answer++;
		}
	}
	//cout << "ȸ�� �� ��" << endl;
	for (int row = 0; row < N; row++) {
		if (check_rot_row(row) == 1) {
			//cout << row + 1 << "�� ���� ����" << endl;
			Answer++;
		}
	}
}

void rot_map() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			rotMap[i][j][0] = map[j][i][0];
			rotMap[i][j][1] = 0;
		}
	}
}

void Input() {
	cin >> N >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j][0];
			map[i][j][1] = 0;
		}
	}
	rot_map();
}


int main(void) {
	Input();
	Solution();
	cout << Answer << endl;
	return 0;
}