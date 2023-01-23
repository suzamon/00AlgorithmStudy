/*
��ŸƮ��ũ�� �繫���� 1��1ũ���� ���簢������ �������� �ִ� N��M ũ���� ���簢������ ��Ÿ�� �� �ִ�.
�繫�ǿ��� �� K���� CCTV�� ��ġ�Ǿ��� �ִµ�, CCTV�� 5���� ������ �ִ�. �� CCTV�� ������ �� �ִ� ����� ������ ����.

1�� CCTV�� �� �� ���⸸ ������ �� �ִ�. 2���� 3���� �� ������ ������ �� �ִµ�,
2���� �����ϴ� ������ ���� �ݴ�����̾�� �ϰ�, 3���� ���� �����̾�� �Ѵ�. 4���� �� ����, 5���� �� ������ ������ �� �ִ�.
CCTV�� ������ �� �ִ� ���⿡ �ִ� ĭ ��ü�� ������ �� �ִ�. �繫�ǿ��� ���� �ִµ�, CCTV�� ���� ����� �� ����.
CCTV�� ������ �� ���� ������ �簢������ �Ѵ�.
CCTV�� ȸ����ų �� �ִµ�, ȸ���� �׻� 90�� �������� �ؾ� �ϸ�, �����Ϸ��� �ϴ� ������ ���� �Ǵ� ���� �����̾�� �Ѵ�.

�������� 0�� �� ĭ, 6�� ��, 1~5�� CCTV�� ��ȣ�̴�.

CCTV�� CCTV�� ����� �� �ִ�. �Ʒ� ���ø� ����.

�繫���� ũ��� ����, �׸��� CCTV�� ������ �־����� ��, CCTV�� ������ ������ ���ؼ�,
�簢 ������ �ּ� ũ�⸦ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

�Է�
ù° �ٿ� �繫���� ���� ũ�� N�� ���� ũ�� M�� �־�����. (1 �� N, M �� 8)
��° �ٺ��� N���� �ٿ��� �繫�� �� ĭ�� ������ �־�����. 0�� �� ĭ, 6�� ��, 1~5�� CCTV�� ��Ÿ����,
�������� ������ CCTV�� �����̴�.
CCTV�� �ִ� ������ 8���� ���� �ʴ´�.

���
ù° �ٿ� �簢 ������ �ּ� ũ�⸦ ����Ѵ�.

N, M, cctvCnt, map[8][8], cctv[8][4] -> x, y, cctv ����, ����

1. Input()
	N, M, map[N][M], cctv[8][2] (1~5)

2. Solution()
	1. cctvCnt��ŭ DFS�� ���� ���ϱ�
		1, 3, 4 -> 0,1,2,3,4 ����
		2 -> 0,1 ����
		5 -> 0 ����
	2. cctvCnt�� �ùķ��̼� ����
*/


#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, M, cctvCnt, emptyCnt, copyEmptyCnt, Answer = -1;
int map[9][9], copyMap[9][9], cctv[9][4];

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void print_cctv() {
	for (int i = 0; i < cctvCnt; i++) {
		cout << '(' << cctv[i][0] << ", " << cctv[i][1] << ")�� " << cctv[i][2] << "�� cctv ����: " << cctv[i][3] << endl;
	}
	cout << endl;
}

void sim_cctv(int dir, int startX, int startY) {
	int nextX, nextY;

	while (1) {
		nextX = startX + dx[dir];
		nextY = startY + dy[dir];
		if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) break;

		if (copyMap[nextX][nextY] == 0) {
			copyEmptyCnt--;
			copyMap[nextX][nextY] = 7;
			startX = nextX;
			startY = nextY;
		}
		else if (copyMap[nextX][nextY] == 6) {
			break;
		}
		else {
			startX = nextX;
			startY = nextY;
		}
	}

}

void mark_cctv(int cctvNum, int startX, int startY, int dir) {
	int nextX, nextY;
	if (cctvNum == 1) {
		sim_cctv(dir, startX, startY);
	}
	else if (cctvNum == 2) {
		if (dir == 0) {
			sim_cctv(1, startX, startY);
			sim_cctv(3, startX, startY);
		}
		else {
			sim_cctv(0, startX, startY);
			sim_cctv(2, startX, startY);
		}
	}
	else if (cctvNum == 3) {
		if (dir == 3) {
			sim_cctv(dir, startX, startY);
			sim_cctv(0, startX, startY);
		}
		else {
			sim_cctv(dir, startX, startY);
			sim_cctv(dir + 1, startX, startY);
		}
	}
	else if (cctvNum == 4) {
		if (dir == 0) {
			sim_cctv(3, startX, startY);
			sim_cctv(0, startX, startY);
			sim_cctv(1, startX, startY);
		}
		else if (dir == 1) {
			sim_cctv(0, startX, startY);
			sim_cctv(1, startX, startY);
			sim_cctv(2, startX, startY);
		}
		else if (dir == 2) {
			sim_cctv(2, startX, startY);
			sim_cctv(3, startX, startY);
			sim_cctv(1, startX, startY);
		}
		else {
			sim_cctv(0, startX, startY);
			sim_cctv(2, startX, startY);
			sim_cctv(3, startX, startY);
		}
	}
	else {
		for (int d = 0; d < 4; d++) {
			sim_cctv(d, startX, startY);
		}
	}
}

void Simulation() {
	for (int i = 0; i < cctvCnt; i++) {
		mark_cctv(cctv[i][2], cctv[i][0], cctv[i][1], cctv[i][3]);
	}

	if (Answer == -1) Answer = copyEmptyCnt;
	else if (Answer > copyEmptyCnt) Answer = copyEmptyCnt;
}

void copy_map() {
	copyEmptyCnt = emptyCnt;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			copyMap[i][j] = map[i][j];
		}
	}
}

void DFS(int cnt) {
	if (cnt == cctvCnt) {
		//print_cctv();
		copy_map();
		Simulation();
		return;
	}

	int cctvNum = cctv[cnt][2];
	if (Answer == 0) return;

	switch (cctvNum) {
	case 1:case 3: case 4:
		for (int i = 0; i < 4; i++) {
			cctv[cnt][3] = i;
			DFS(cnt + 1);
			if (Answer == 0) return;
		}
		break;
	case 2:
		for (int i = 0; i < 2; i++) {
			cctv[cnt][3] = i;
			DFS(cnt + 1);
			if (Answer == 0) return;
		}
		break;
	case 5:
		cctv[cnt][3] = 0;
		DFS(cnt + 1);
		if (Answer == 0) return;
		break;
	}
}

void Solution() {
	DFS(0);
}

void Input() {
	cctvCnt = 0;
	emptyCnt = 0;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] > 0 && map[i][j] < 6) {
				cctv[cctvCnt][0] = i;
				cctv[cctvCnt][1] = j;
				cctv[cctvCnt][2] = map[i][j];
				cctvCnt++;
			}
			else if (map[i][j] == 0) emptyCnt++;
		}
	}
}

int main(void) {
	Input();
	Solution();
	cout << Answer << endl;
	return 0;
}