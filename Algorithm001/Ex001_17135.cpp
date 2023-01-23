/*
ĳ�� ���潺�� ���� ���� �������� ���� ��� �� ����� ���� -> NxM ���������� ��Ÿ��
�������� 1x1 ũ���� ĭ���� �������� �ְ�, �� ĭ�� ���Ե� ���� ���� �ִ� �ϳ�
�������� N�� �� �ٷ� �Ʒ����� ��� ĭ�� ���� �ִ�
���� ��Ű�� ���� �ü� 3�� ��ġ, �ü��� ���� �ִ� ĭ ��ġ & �ϳ��� ĭ���� �ִ� 1���� �ü�
������ �ϸ��� �ü��� D �Ÿ� ������ �� �߿� ���� ����� �� &  ���� ��� ���� ������ ���� ���� & ���� ���� ���� �ü��� ������ ����
���ݹ��� ���� ���� ���� -> ���� ������ ���� �Ʒ��� ��ĭ �̵�, ���� �ִ� ĭ���� �̵��� ��� ���ӿ��� ����
��� ���� ���ܵǸ� ���� �� & �������� ������ �� �ִ� ���� �ִ� ���� ���

�Ÿ� : (r1, c1), (r2, c2)�� �Ÿ��� |r1-r2| + |c1-c2|

N, M, D (3 �� N, M �� 15, 1 �� D �� 10)

1. Input() : N, M, D, map[N+1][M], arrow[3][2]

2. Solution() :
	1) void find_arrow(int startRow, int cnt) : DFS�� ���� �ü� ��ġ 3�� ���ϱ� ���� cnt==3�̸� simulation()
	2) int simulation() 1)���� �ü� ��ġ�� �������� ���� -> �ü��� ���� �� �ִ� �� Ž��
		2-1) kill_enermy[3][2]�� ���� ��ġ ���ǿ� ���� �� ����
		2-2) 2-1)���� ã�� �� ����
		2-3) ��ĭ�� ������
		2-4) ĭ�� ���� �Ѹ� ������ ����
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>

int N, M, D, enermyNum, Answer = 0;
int map[16][15];
int simMap[16][15];
int arrow[3][2] = { 0, };

using namespace std;

void copy_map() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			simMap[i][j] = map[i][j];
		}
	}
}

int simulation() {
	int exitNum, killNum = 0;
	int arrowX, arrowY, curD, nextD;
	int kill[3][2];
	int tmpArr[15];

	exitNum = enermyNum;

	while (1) {
		//������ �� ã��
		for (int arrowIdx = 0; arrowIdx < 3; arrowIdx++) {
			arrowX = arrow[arrowIdx][0];
			arrowY = arrow[arrowIdx][1];
			curD = 0;
			nextD = 0;
			kill[arrowIdx][0] = -1;
			kill[arrowIdx][1] = -1;
			for (int i = N - 1; i >= 0; i--) {
				if (abs(arrowX - i) > D) break;
				for (int j = 0; j < M; j++) {
					if (simMap[i][j] != 0) {
						if (curD == 0) {
							curD = abs(arrowX - i) + abs(arrowY - j);
							if (curD > D) {
								curD = 0;
								continue;
							}
							kill[arrowIdx][0] = i;
							kill[arrowIdx][1] = j;
						}
						else {
							nextD = abs(arrowX - i) + abs(arrowY - j);
							if (nextD < curD) {
								kill[arrowIdx][0] = i;
								kill[arrowIdx][1] = j;
								curD = nextD;
							}
							else if (nextD == curD && kill[arrowIdx][1] > j) {
								kill[arrowIdx][0] = i;
								kill[arrowIdx][1] = j;
								curD = nextD;
							}
						}
					}
				}
				
			}

		}

		//�� ����
		for (int i = 0; i < 3; i++) {
			arrowX = kill[i][0];
			arrowY = kill[i][1];
			if (arrowX == -1 && arrowY == -1) continue;
			if (simMap[arrowX][arrowY] == 1) {
				exitNum--;
				simMap[arrowX][arrowY] = 0;
				killNum++;
			}
		}

		//��ĭ�� ������
		for (int i = N - 1; i > 0; i--) {
			for (int j = 0; j < M; j++) {
				if (i == N - 1 && simMap[i][j] == 1) {
					exitNum--;
				}
				simMap[i][j] = simMap[i - 1][j];
			}
		}
		for (int j = 0; j < M; j++) {
			simMap[0][j] = 0;
		}

		if (exitNum <= 0) break;
	}
	
	return killNum;
	
}

void find_arrow(int startCol, int cnt) {
	if (cnt == 3) {
		/*
		cout << "�ü� ��ġ" << endl;
		for (int i = 0; i < 3; i++) {
			cout << arrow[i][0] << ", " << arrow[i][1] << endl;
		}
		cout << endl;
		*/
		int tmp_answer;

		copy_map();

		tmp_answer = simulation();
		if (tmp_answer > Answer) Answer = tmp_answer;

	}

	for (int i = startCol; i < M; i++) {
		arrow[cnt][1] = i;
		find_arrow(i + 1, cnt + 1);
	}
}

void Solution() {
	for (int i = 0; i < 3; i++) {
		arrow[i][0] = N;
	}

	for (int i = 0; i <= M - 3; i++) {
		arrow[0][1] = i;
		find_arrow(i + 1, 1);
	}
}

void Input() {
	cin >> N >> M >> D;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) enermyNum++;
		}
	}
}

int main(void) {
	Input();
	Solution();

	cout << Answer << endl;

	return 0;
}