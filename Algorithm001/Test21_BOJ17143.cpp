/*
���ÿ��� ��� ���ø� �ϴ� ���� ũ�Ⱑ R��C�� ���������� ��Ÿ�� �� �ִ�.
�������� �� ĭ�� (r, c)�� ��Ÿ�� �� �ִ�. r�� ��, c�� ���̰�, (R, C)�� �Ʒ� �׸����� ���� ������ �Ʒ��� �ִ� ĭ�̴�.
ĭ���� �� �ִ� �� ���� ������� �� �ִ�. ���� ũ��� �ӵ��� ������ �ִ�.

���ÿ��� ó���� 1�� ���� �� ĭ ���ʿ� �ִ�. ������ 1�� ���� �Ͼ�� ���̸�, �Ʒ� ���� ������� �Ͼ��.
���ÿ��� ���� ������ ���� ������ ĭ�� �̵��ϸ� �̵��� �����.

1. ���ÿ��� ���������� �� ĭ �̵��Ѵ�.
2. ���ÿ��� �ִ� ���� �ִ� ��� �߿��� ���� ���� ����� �� ��´�. �� ������ �����ǿ��� ���� �� �������.
3. �� �̵��Ѵ�.

���� �Է����� �־��� �ӵ��� �̵��ϰ�, �ӵ��� ������ ĭ/���̴�.
�� �̵��Ϸ��� �ϴ� ĭ�� �������� ��踦 �Ѵ� ��쿡�� ������ �ݴ�� �ٲ㼭 �ӷ��� ������ä�� �̵��Ѵ�.

���� �׸��� ���¿��� 1�ʰ� ������ ������ ���°� �ȴ�.
�� ���� �ִ� ������ �ӵ��� ����, ���� �Ʒ��� ���� ������ �ӷ��̴�.
���� ���� �� �����ϱ� ���� ���ڸ� ������.

�� �̵��� ��ģ �Ŀ� �� ĭ�� �� �� ���� �̻� ���� �� �ִ�.
�̶��� ũ�Ⱑ ���� ū �� ������ �� ��� ��ƸԴ´�.

���ÿ��� ��� ���ø� �ϴ� �������� ���°� �־����� ��, ���ÿ��� ���� ��� ũ���� ���� ���غ���.


�Է�
ù° �ٿ� �������� ũ�� R, C�� ����� �� M�� �־�����. (2 �� R, C �� 100, 0 �� M �� R��C)

��° �ٺ��� M���� �ٿ� ����� ������ �־�����.
����� ������ �ټ� ���� r, c, s, d, z (1 �� r �� R, 1 �� c �� C, 0 �� s �� 1000, 1 �� d �� 4, 1 �� z �� 10000) �� �̷���� �ִ�.
(r, c)�� ����� ��ġ, s�� �ӷ�, d�� �̵� ����, z�� ũ���̴�.
d�� 1�� ���� ��, 2�� ���� �Ʒ�, 3�� ���� ������, 4�� ���� ������ �ǹ��Ѵ�.

�� �� ���� ũ�⸦ ���� ���� ����, �ϳ��� ĭ�� �� �̻��� �� �ִ� ���� ����.

���
���ÿ��� ���� ��� ũ���� ���� ����Ѵ�.

int R, C, M, Answer;
int personCol;

deque <int> shark[5] (r, c, s, d, z) (r, c)�� ����� ��ġ, s�� �ӷ�, d�� �̵� ����, z�� ũ��

int dx[5] = {0, -1, 1, 0, 0};
int dy[5] = {0, 0, 0, 1, -1};


1. Input()
	R, C, M, shark[0]~shark[4]�� ����

2. Solution()
	1) find_shark(int col) -> for(col=1; col<=C; col++) �ݺ�
		1-1) int map[101][101] = {0, };
		1-2) shark ���鼭 map�� (idx + 1) ǥ�� (size[4] = -1�� ��쿡�� ���� ���
		1-2-1) map�� ǥ���ϸ鼭 '0'�� �ƴ� ��쿡�� ���Ե� idx ��� ũ��� ������ idx ��� ũ�� ���ؼ�
				���� ũ�� ��� ������[4]�� -1�� ����
		1-2-2) map�� '0'���� ǥ��Ǿ� ������ �׳� ����
		1-3) map�� ǥ�Ⱑ ���� ��쿡�� �ش� col���� row ���� ���� ���� ��� ���� -> Answer�� ũ�� �߰�
		1-4) ���� ��� ������� -1�� ����
	2) move_shark()
		2-1) shark Ž�� ���� -> shark[0].size �����ؼ� �ݺ�!
		2-2) r, c, s, d, z �� ���� -> z = -1�̸� �׳� pop�� ����
		2-3) ��� ���⿡ �°Բ� ��ġ ����
		2-4) ���ŵ� �� shark�� ����(push_back)
	3) �ݺ��� ������ Answer �� ���

*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int R, C, M, Answer = 0;
int personCol;

deque <int> shark[5]; //(r, c, s, d, z) (r, c)�� ����� ��ġ, s�� �ӷ�, d�� �̵� ����, z�� ũ��

int dx[5] = { 0, -1, 1, 0, 0 };
int dy[5] = { 0, 0, 0, 1, -1 };


void find_shark(int col) {
	int map[101][101] = { 0, };
	int arr[5];
	int tmpIdx, tmpSize;

	for (int idx = 0; idx < shark[0].size(); idx++) {
		arr[4] = shark[4][idx];
		if (arr[4] == -1) continue;

		for (int i = 0; i < 4; i++) {
			arr[i] = shark[i][idx];
		}

		if (map[arr[0]][arr[1]] == 0) {
			map[arr[0]][arr[1]] = idx + 1;
		}
		else {
			tmpIdx = map[arr[0]][arr[1]] - 1;
			tmpSize = shark[4][tmpIdx];
			if (arr[4] < tmpSize) {
				shark[4][idx] = -1;
			}
			else {
				shark[4][tmpIdx] = -1;
				map[arr[0]][arr[1]] = idx + 1;
			}
		}
	}

	for (int row = 1; row <= R; row++) {

		if (map[row][col] > 0) {
			tmpIdx = map[row][col] - 1;
			Answer = Answer + shark[4][tmpIdx];
			shark[4][tmpIdx] = -1;
			//cout << col << "������ ";
			//printf("%c", 'A' + tmpIdx);
			//cout << "��° ��� ����" << endl;
			map[row][col] = 0;
			break;
		}

	}
	/*
	cout << "��" << endl;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	*/
}

void move_shark() {
	int r, c, s, d, z, nR, nC, nS, nD, tmp;
	int tmpSize = shark[0].size();
	for (int idx = 0; idx < tmpSize; idx++) {
		z = shark[4].front();
		shark[4].pop_front();
		if (z == -1) {
			for (int i = 0; i < 4; i++) {
				tmp = shark[i].front();
				shark[i].pop_front();
				shark[i].push_back(tmp);
			}
			shark[4].push_back(-1);
			continue;
		}
		r = shark[0].front();
		c = shark[1].front();
		s = shark[2].front();
		nS = s;
		d = shark[3].front();
		for (int i = 0; i < 4; i++) {
			shark[i].pop_front();
		}

		switch (d) {
		case 1:
			if (r - s >= 1) {
				nR = r - s;
				nD = 1;
			}
			else {
				s = s - (r - 1);
				while (1) {
					if ((1 + s) >= 1 && (1 + s) <= R) {
						nR = 1 + s;
						nD = 2;
						break;
					}
					s = s - (R - 1);
					if ((R - s) >= 1 && (R - s) <= R) {
						nR = R - s;
						nD = 1;
						break;
					}
					s = s - (R - 1);
				}
			}
			shark[0].push_back(nR);
			shark[1].push_back(c);
			shark[2].push_back(nS);
			shark[3].push_back(nD);
			shark[4].push_back(z);
			break;
		case 2:
			if (r + s <= R) {
				nR = r + s;
				nD = 2;
			}
			else {
				s = s - (R - r);
				while (1) {
					if ((R - s) >= 1 && (R - s) <= R) {
						nR = R - s;
						nD = 1;
						break;
					}
					s = s - (R - 1);
					if ((1 + s) >= 1 && (1 + s) <= R) {
						nR = 1 + s;
						nD = 2;
						break;
					}
					s = s - (R - 1);
				}
			}
			shark[0].push_back(nR);
			shark[1].push_back(c);
			shark[2].push_back(nS);
			shark[3].push_back(nD);
			shark[4].push_back(z);
			break;
		case 3:
			if (c + s <= C) {
				nC = c + s;
				nD = 3;
			}
			else {
				s = s - (C - c);
				while (1) {
					if ((C - s) >= 1 && (C - s) <= C) {
						nC = C - s;
						nD = 4;
						break;
					}
					s = s - (C - 1);
					if ((1 + s) >= 1 && (1 + s) <= C) {
						nC = 1 + s;
						nD = 3;
						break;
					}
					s = s - (C - 1);
				}
			}
			shark[0].push_back(r);
			shark[1].push_back(nC);
			shark[2].push_back(nS);
			shark[3].push_back(nD);
			shark[4].push_back(z);
			break;
		case 4:
			if (c - s >= 1) {
				nC = c - s;
				nD = 4;
			}
			else {
				s = s - (c - 1);
				while (1) {
					if ((1 + s) >= 1 && (1 + s) <= C) {
						nC = 1 + s;
						nD = 3;
						break;
					}
					s = s - (C - 1);
					if ((C - s) >= 1 && (C - s) <= C) {
						nC = C - s;
						nD = 4;
						break;
					}
					s = s - (C - 1);
				}
			}
			shark[0].push_back(r);
			shark[1].push_back(nC);
			shark[2].push_back(nS);
			shark[3].push_back(nD);
			shark[4].push_back(z);
			break;
		}
	}
}

void Solution() {
	for (int col = 1; col <= C; col++) {
		find_shark(col);
		move_shark();
	}
	cout << Answer << endl;
}

void Input() {
	int tmp;
	cin >> R >> C >> M;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> tmp;
			shark[j].push_back(tmp);
		}
	}
}

int main(void) {

	Input();
	Solution();


	return 0;
}