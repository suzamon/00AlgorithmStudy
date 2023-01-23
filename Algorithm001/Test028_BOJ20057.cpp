/*
1'03''06'''
������ �� ����̵��� �����, ������ ����̵��� ũ�Ⱑ N��N�� ���ڷ� �������� �𷡹翡�� �����Ϸ��� �Ѵ�.
��ġ (r, c)�� ������ r�� c���� �ǹ��ϰ�, A[r][c]�� (r, c)�� �ִ� ���� ���� �ǹ��Ѵ�.

����̵��� �����ϸ� ������ ��� ĭ���� ����̵��� �̵��� ���۵ȴ�. ����̵��� �� ���� �� ĭ �̵��Ѵ�.
������ N = 7�� ��� ����̵��� �̵��̴�.

����̵��� �� ĭ �̵��� ������ �𷡴� ������ ���� ������ ������ �𳯸��� �ȴ�.

����̵��� x���� y�� �̵��ϸ�, y�� ��� �𷡰� ������ �ᰡ �����ִ� ĭ���� �̵��Ѵ�.
������ �����ִ� ĭ���� �̵��ϴ� ���� ���� y�� �ִ� ���� �ش� ������ŭ�̰�, ��꿡�� �Ҽ��� �Ʒ��� ������.
��� �̵��ϴ� ���� ���� ������ �����ִ� ĭ���� �̵����� ���� ���� ���� ��� ����.
�𷡰� �̹� �ִ� ĭ���� �𷡰� �̵��ϸ�, ���� ���� ��������. ���� �׸��� ����̵��� �������� �̵��� ���̰�,
�ٸ� �������� �̵��ϴ� ���� ���� �׸��� �ش� �������� ȸ���ϸ� �ȴ�.

����̵��� (1, 1)���� �̵��� �� �Ҹ��Ѵ�. �𷡰� ������ ������ �̵��� ���� �ִ�. ����̵��� �Ҹ�Ǿ��� ��,
������ ������ ���� ���� ���� ���غ���.


�Է�
ù° �ٿ� ������ ũ�� N�� �־�����. ��° �ٺ��� N���� �ٿ��� ������ �� ĭ�� �ִ� �𷡰� �־�����.
r��° �ٿ��� c��° �־����� ������ A[r][c] �̴�.

���
������ ������ ���� ���� ���� ����Ѵ�.

����
3 �� N �� 499
N�� Ȧ��
0 �� A[r][c] �� 1,000
��� ĭ�� �ִ� ���� ���� 0

N, cnt, dir, sX, sY, Answer =0;
int arr[501][501]


1. Input()
	N, arr �Է� & sX = N/2 +1, SY = SX;
2. Soltion()
	0) cnt = 0, dir =1;
	1) while(1)
	2) cnt++;
	3) for(int i=0; i<cnt; i++) move_tornedo(int sX, int sY)
	5) if(sX=1 && sY ==1) break;
	4) dir++;
	5) for(int i=0; i<cnt; i++) move_tornedo(int sX, int sY)
	6) cnt++;
	7) dir++;
	8) for(int i=0; i<cnt; i++) move_tornedo(int sX, int sY)
	9) dir++;
	10) for(int i=0; i<cnt; i++) move_tornedo(int sX, int sY)

* move_torneido()
	1) nX = sX + dx[dir], nY = sY + dy[dir]
	2) sand = arr[nX][nY], arr[nX][nY] = 0
	3) spread_sand(sand, nX, nY, dir)
	4) sX = nX, sY = nY
	5) return

* spread_sand(int sand, int nX, int nY)
	0) tmpX, tmpY, tmpSand
	1) switch (dir) case 1: case 4: break; case 2: case 3: break;
	2) dir�� �°Բ� ���� & tmpX, tmpY�� ������ �Ѿ�� Answer�� �߰�
*/


#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, cnt, dir, sX, sY, Answer = 0;

int arr[501][501] = { 0, };

int dx[5] = { 0, 0, 1,0, -1 };
int dy[5] = { 0, -1, 0, 1, 0 };

void print_Info() {
	cout << "����̵� ��ġ: " << sX << ", " << sY << endl;;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << arr[i][j] << ' ';
		}
		cout << endl;
	}
}

bool inRange(int x, int y) {
	if (x < 1 || x > N || y < 1 || y > N) return false;
	
	return true;
}

void spread_sand(int sand, int nX, int nY) {
	int tmpX, tmpY, tmpSand, alpha = sand;

	switch (dir) {
	case 1:
		tmpX = nX;
		tmpY = nY - 2;
		tmpSand = (int) sand * 0.05;
		alpha = alpha - tmpSand;
		if (inRange(tmpX, tmpY)) arr[tmpX][tmpY] = arr[tmpX][tmpY] + tmpSand;
		else Answer = Answer + tmpSand;

		tmpY = nY + 1;
		for (tmpX = nX - 1; tmpX <= nX + 1; tmpX++) {
			if (tmpX == nX) continue;

			tmpSand = (int)sand * 0.01;
			alpha = alpha - tmpSand;
			if (inRange(tmpX, tmpY)) arr[tmpX][tmpY] = arr[tmpX][tmpY] + tmpSand;
			else Answer = Answer + tmpSand;
		}

		tmpY = nY;
		for (tmpX = nX - 2; tmpX <= nX + 2; tmpX++) {
			if (tmpX == nX) continue;
			else if (tmpX == nX - 2 || tmpX == nX + 2) tmpSand = (int)sand * 0.02;
			else tmpSand = (int)sand * 0.07;

			alpha = alpha - tmpSand;
			if (inRange(tmpX, tmpY)) arr[tmpX][tmpY] = arr[tmpX][tmpY] + tmpSand;
			else Answer = Answer + tmpSand;
		}

		tmpY = nY - 1;
		for (tmpX = nX - 1; tmpX <= nX + 1; tmpX++) {
			if (tmpX == nX) continue;

			tmpSand = (int)sand * 0.1;
			alpha = alpha - tmpSand;
			if (inRange(tmpX, tmpY)) arr[tmpX][tmpY] = arr[tmpX][tmpY] + tmpSand;
			else Answer = Answer + tmpSand;
		}
		tmpX = nX, tmpY = nY - 1;
		if (inRange(tmpX, tmpY)) arr[tmpX][tmpY] = arr[tmpX][tmpY] + alpha;
		else Answer = Answer + alpha;
		break;
	case 2:
		tmpX = nX + 2;
		tmpY = nY;
		tmpSand = (int)sand * 0.05;
		alpha = alpha - tmpSand;
		if (inRange(tmpX, tmpY)) arr[tmpX][tmpY] = arr[tmpX][tmpY] + tmpSand;
		else Answer = Answer + tmpSand;

		tmpX = nX - 1;
		for (tmpY = nY - 1; tmpY <= nY + 1; tmpY++) {
			if (tmpY == nY) continue;

			tmpSand = (int)sand * 0.01;
			alpha = alpha - tmpSand;
			if (inRange(tmpX, tmpY)) arr[tmpX][tmpY] = arr[tmpX][tmpY] + tmpSand;
			else Answer = Answer + tmpSand;
		}

		tmpX = nX;
		for (tmpY = nY - 2; tmpY <= nY + 2; tmpY++) {
			if (tmpY == nY) continue;
			else if (tmpY == nY - 2 || tmpY == nY + 2) tmpSand = (int)sand * 0.02;
			else tmpSand = (int)sand * 0.07;

			alpha = alpha - tmpSand;
			if (inRange(tmpX, tmpY)) arr[tmpX][tmpY] = arr[tmpX][tmpY] + tmpSand;
			else Answer = Answer + tmpSand;
		}

		tmpX = nX + 1;
		for (tmpY = nY - 1; tmpY <= nY + 1; tmpY++) {
			if (tmpY == nY) continue;

			tmpSand = (int)sand * 0.1;
			alpha = alpha - tmpSand;
			if (inRange(tmpX, tmpY)) arr[tmpX][tmpY] = arr[tmpX][tmpY] + tmpSand;
			else Answer = Answer + tmpSand;
		}

		tmpX = nX + 1, tmpY = nY;
		if (inRange(tmpX, tmpY)) arr[tmpX][tmpY] = arr[tmpX][tmpY] + alpha;
		else Answer = Answer + alpha;
		break;
	case 3:
		tmpX = nX;
		tmpY = nY + 2;
		tmpSand = (int)sand * 0.05;
		alpha = alpha - tmpSand;
		if (inRange(tmpX, tmpY)) arr[tmpX][tmpY] = arr[tmpX][tmpY] + tmpSand;
		else Answer = Answer + tmpSand;

		tmpY = nY - 1;
		for (tmpX = nX - 1; tmpX <= nX + 1; tmpX++) {
			if (tmpX == nX) continue;

			tmpSand = (int)sand * 0.01;
			alpha = alpha - tmpSand;
			if (inRange(tmpX, tmpY)) arr[tmpX][tmpY] = arr[tmpX][tmpY] + tmpSand;
			else Answer = Answer + tmpSand;
		}

		tmpY = nY;
		for (tmpX = nX - 2; tmpX <= nX + 2; tmpX++) {
			if (tmpX == nX) continue;
			else if (tmpX == nX - 2 || tmpX == nX + 2) tmpSand = (int)sand * 0.02;
			else tmpSand = (int)sand * 0.07;

			alpha = alpha - tmpSand;
			if (inRange(tmpX, tmpY)) arr[tmpX][tmpY] = arr[tmpX][tmpY] + tmpSand;
			else Answer = Answer + tmpSand;
		}

		tmpY = nY + 1;
		for (tmpX = nX - 1; tmpX <= nX + 1; tmpX++) {
			if (tmpX == nX) continue;

			tmpSand = (int)sand * 0.1;
			alpha = alpha - tmpSand;
			if (inRange(tmpX, tmpY)) arr[tmpX][tmpY] = arr[tmpX][tmpY] + tmpSand;
			else Answer = Answer + tmpSand;
		}

		tmpX = nX, tmpY = nY + 1;
		if (inRange(tmpX, tmpY)) arr[tmpX][tmpY] = arr[tmpX][tmpY] + alpha;
		else Answer = Answer + alpha;
		break;
	case 4:
		tmpX = nX - 2;
		tmpY = nY;
		tmpSand = (int)sand * 0.05;
		alpha = alpha - tmpSand;
		if (inRange(tmpX, tmpY)) arr[tmpX][tmpY] = arr[tmpX][tmpY] + tmpSand;
		else Answer = Answer + tmpSand;

		tmpX = nX + 1;
		for (tmpY = nY - 1; tmpY <= nY + 1; tmpY++) {
			if (tmpY == nY) continue;

			tmpSand = (int)sand * 0.01;
			alpha = alpha - tmpSand;
			if (inRange(tmpX, tmpY)) arr[tmpX][tmpY] = arr[tmpX][tmpY] + tmpSand;
			else Answer = Answer + tmpSand;
		}

		tmpX = nX;
		for (tmpY = nY - 2; tmpY <= nY + 2; tmpY++) {
			if (tmpY == nY) continue;
			else if (tmpY == nY - 2 || tmpY == nY + 2) tmpSand = (int)sand * 0.02;
			else tmpSand = (int)sand * 0.07;

			alpha = alpha - tmpSand;
			if (inRange(tmpX, tmpY)) arr[tmpX][tmpY] = arr[tmpX][tmpY] + tmpSand;
			else Answer = Answer + tmpSand;
		}

		tmpX = nX - 1;
		for (tmpY = nY - 1; tmpY <= nY + 1; tmpY++) {
			if (tmpY == nY) continue;

			tmpSand = (int)sand * 0.1;
			alpha = alpha - tmpSand;
			if (inRange(tmpX, tmpY)) arr[tmpX][tmpY] = arr[tmpX][tmpY] + tmpSand;
			else Answer = Answer + tmpSand;
		}
		tmpX = nX - 1, tmpY = nY;
		if (inRange(tmpX, tmpY)) arr[tmpX][tmpY] = arr[tmpX][tmpY] + alpha;
		else Answer = Answer + alpha;
		break;

	}
}

void move_tornedo() {
	int nX, nY, sand;
	nX = sX + dx[dir];
	nY = sY + dy[dir];

	sand = arr[nX][nY];
	arr[nX][nY] = 0;
	if (sand > 0) {
		spread_sand(sand, nX, nY);
	}
	sX = nX, sY = nY;
	//print_Info();
	return;
}

void Solution() {
	cnt = 0, dir = 1;

	while (1) {
		cnt++;
		for (int i = 0; i < cnt; i++) {
			move_tornedo();
			if (sX == 1 && sY == 1) break;
		}
		if (sX == 1 && sY == 1) break;

		dir++;
		for (int i = 0; i < cnt; i++) {
			move_tornedo();
		}

		cnt++;
		dir++;
		for (int i = 0; i < cnt; i++) {
			move_tornedo();
		}

		dir++;
		for (int i = 0; i < cnt; i++) {
			move_tornedo();
		}

		dir = 1;
	}
}

void Input() {
	cin >> N;
	sX = N / 2 + 1, sY = N / 2 + 1;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
}

int main(void) {
	Input();
	Solution();
	cout << Answer << endl;
	return 0;
}