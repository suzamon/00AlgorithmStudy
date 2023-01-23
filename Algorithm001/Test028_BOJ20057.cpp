/*
1'03''06'''
마법사 상어가 토네이도를 배웠고, 오늘은 토네이도를 크기가 N×N인 격자로 나누어진 모래밭에서 연습하려고 한다.
위치 (r, c)는 격자의 r행 c열을 의미하고, A[r][c]는 (r, c)에 있는 모래의 양을 의미한다.

토네이도를 시전하면 격자의 가운데 칸부터 토네이도의 이동이 시작된다. 토네이도는 한 번에 한 칸 이동한다.
다음은 N = 7인 경우 토네이도의 이동이다.

토네이도가 한 칸 이동할 때마다 모래는 다음과 같이 일정한 비율로 흩날리게 된다.

토네이도가 x에서 y로 이동하면, y의 모든 모래가 비율과 α가 적혀있는 칸으로 이동한다.
비율이 적혀있는 칸으로 이동하는 모래의 양은 y에 있는 모래의 해당 비율만큼이고, 계산에서 소수점 아래는 버린다.
α로 이동하는 모래의 양은 비율이 적혀있는 칸으로 이동하지 않은 남은 모래의 양과 같다.
모래가 이미 있는 칸으로 모래가 이동하면, 모래의 양은 더해진다. 위의 그림은 토네이도가 왼쪽으로 이동할 때이고,
다른 방향으로 이동하는 경우는 위의 그림을 해당 방향으로 회전하면 된다.

토네이도는 (1, 1)까지 이동한 뒤 소멸한다. 모래가 격자의 밖으로 이동할 수도 있다. 토네이도가 소멸되었을 때,
격자의 밖으로 나간 모래의 양을 구해보자.


입력
첫째 줄에 격자의 크기 N이 주어진다. 둘째 줄부터 N개의 줄에는 격자의 각 칸에 있는 모래가 주어진다.
r번째 줄에서 c번째 주어지는 정수는 A[r][c] 이다.

출력
격자의 밖으로 나간 모래의 양을 출력한다.

제한
3 ≤ N ≤ 499
N은 홀수
0 ≤ A[r][c] ≤ 1,000
가운데 칸에 있는 모래의 양은 0

N, cnt, dir, sX, sY, Answer =0;
int arr[501][501]


1. Input()
	N, arr 입력 & sX = N/2 +1, SY = SX;
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
	2) dir에 맞게끔 수정 & tmpX, tmpY가 범위에 넘어서면 Answer에 추가
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
	cout << "토네이도 위치: " << sX << ", " << sY << endl;;
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