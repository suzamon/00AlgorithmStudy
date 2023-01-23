/*
스타트링크에서 판매하는 어린이용 장난감 중에서 가장 인기가 많은 제품은 구슬 탈출이다.
구슬 탈출은 직사각형 보드에 빨간 구슬과 파란 구슬을 하나씩 넣은 다음, 빨간 구슬을 구멍을 통해 빼내는 게임이다.

보드의 세로 크기는 N, 가로 크기는 M이고, 편의상 1×1크기의 칸으로 나누어져 있다.
가장 바깥 행과 열은 모두 막혀져 있고, 보드에는 구멍이 하나 있다.
빨간 구슬과 파란 구슬의 크기는 보드에서 1×1크기의 칸을 가득 채우는 사이즈이고, 각각 하나씩 들어가 있다.
게임의 목표는 빨간 구슬을 구멍을 통해서 빼내는 것이다. 이때, 파란 구슬이 구멍에 들어가면 안 된다.

이때, 구슬을 손으로 건드릴 수는 없고, 중력을 이용해서 이리 저리 굴려야 한다.
왼쪽으로 기울이기, 오른쪽으로 기울이기, 위쪽으로 기울이기, 아래쪽으로 기울이기와 같은 네 가지 동작이 가능하다.

각각의 동작에서 공은 동시에 움직인다. 빨간 구슬이 구멍에 빠지면 성공이지만, 파란 구슬이 구멍에 빠지면 실패이다.
빨간 구슬과 파란 구슬이 동시에 구멍에 빠져도 실패이다. 빨간 구슬과 파란 구슬은 동시에 같은 칸에 있을 수 없다.
또, 빨간 구슬과 파란 구슬의 크기는 한 칸을 모두 차지한다.
기울이는 동작을 그만하는 것은 더 이상 구슬이 움직이지 않을 때 까지이다.

보드의 상태가 주어졌을 때, 최소 몇 번 만에 빨간 구슬을 구멍을 통해 빼낼 수 있는지 구하는 프로그램을 작성하시오.

입력
첫 번째 줄에는 보드의 세로, 가로 크기를 의미하는 두 정수 N, M (3 ≤ N, M ≤ 10)이 주어진다.
다음 N개의 줄에 보드의 모양을 나타내는 길이 M의 문자열이 주어진다.
이 문자열은 '.', '#', 'O', 'R', 'B' 로 이루어져 있다. '.'은 빈 칸을 의미하고, '#'은 공이 이동할 수 없는 장애물 또는 벽을 의미하며,
'O'는 구멍의 위치를 의미한다. 'R'은 빨간 구슬의 위치, 'B'는 파란 구슬의 위치이다.

입력되는 모든 보드의 가장자리에는 모두 '#'이 있다. 구멍의 개수는 한 개 이며, 빨간 구슬과 파란 구슬은 항상 1개가 주어진다.

출력
최소 몇 번 만에 빨간 구슬을 구멍을 통해 빼낼 수 있는지 출력한다.
만약, 10번 이하로 움직여서 빨간 구슬을 구멍을 통해 빼낼 수 없으면 -1을 출력한다.

int N, M, Answer;
char map[11][11], copyMap[11][11];
int dir[11]
int dx[5], dy[5] -> 1: 왼/ 2: 오/ 3: 위/ 4: 아래
int sRed[2], sBlue[2], nRed[2], nBlue[2], hole[2];

1. Input()
	N, M, map[11][11], sRed[2], sBlue[2], hole[2];
2. Solution();
	1) DFS(int cnt)
		1-1) if(cnt == 10)
		1-2) int breakFlag = 0;
		1-2) copy_map(); -> map, nRed, nBlue 복사
		1-2) for(int i=0; i< cnt; i++) {
		1-2) breakFlag = simulation(i);
		1-3) if(breakFlag ==1) break;
		1-2) break;
		1-3) int sdir = dir[cnt-1];
		1-4) if(sdir==1 || sdir==2) for(int d=3; d<=4; d++) dir[cnt] = d, DFS(cnt+1);
		1-5) else if(sdir==3 || sdir==4) for(int d=1; d<=2; d++) dir[cnt] = d, DFS(cnt+1);
	2) int simulation(int time)
		2-1) if(time +1 >= Answer) return 1;
		2-2) int d, sX, sY, nX, nY;
		2-3) d = dir[time];
		2-4) switch(d)
		2-5) case 1: -> innRed[1] & nBlue[1] 비교해서 작은 거 부터
		2-6) case 2: -> nRed[1] & nBlue[1] 비교해서 큰 거 부터
		2-7) case 3: -> nRed[0] & nBlue[0] 비교해서 작은 거 부터
		2-8) case 4: -> nRed[0] & nBlue[0] 비교해서 큰 거 부터

	3) int moveRed(int d, int sX, int sY) -> 이동하면 '1', 가만히 '0', 탈출 '-1'
		3-0) int nX, nY, retFlag = 0;
		3-1) switch(d)
		3-2) case 1:
			nX = sX, nY = sY;
			for(nY = sY;  nY>=0; nY--)
				if(copyMap[nX][nY] == '#' || copyMap[nX][nY] == 'B') nY++, break;
				else if(copyMap[nX][nY] == 'O') retFlag = -1, break;
			if(sX == nX && sY==nY) retFlag = 0, return;
			else if(retFlag == -1) copyMap[sX][sY] = '.', return;
			else copyMap[sX][sY] = '.', copyMap[nX][nY] = 'R', retFlag =1, return;
		3-2) case 2:
			nX = sX, nY = sY;
			for(nY = sY;  nY<M;  nY++)
				if(copyMap[nX][nY] == '#' || copyMap[nX][nY] == 'B') nY--, break;
				else if(copyMap[nX][nY] == 'O') retFlag = -1, break;
			if(sX == nX && sY==nY) retFlag = 0, return;
			else if(retFlag == -1) copyMap[sX][sY] = '.', return;
			else copyMap[sX][sY] = '.', copyMap[nX][nY] = 'R', retFlag =1, return;
		3-3) case 3:
			nX = sX, nY = sY;
			for(nX = sX;  nX>=0; nX--)
				if(copyMap[nX][nY] == '#' || copyMap[nX][nY] == 'B') nX++, break;
				else if(copyMap[nX][nY] == 'O') retFlag = -1, break;
			if(sX == nX && sY==nY) retFlag = 0, return;
			else if(retFlag == -1) copyMap[sX][sY] = '.', return;
			else copyMap[sX][sY] = '.', copyMap[nX][nY] = 'R', retFlag =1, return;
		3-2) case 2:
			nX = sX, nY = sY;
			for(nX = sX;  nX<N; nX++)
				if(copyMap[nX][nY] == '#' || copyMap[nX][nY] == 'B') nX--, break;
				else if(copyMap[nX][nY] == 'O') retFlag = -1, break;
			if(sX == nX && sY==nY) retFlag = 0, return;
			else if(retFlag == -1) copyMap[sX][sY] = '.', return;
			else copyMap[sX][sY] = '.', copyMap[nX][nY] = 'R', retFlag =1, return;

*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int N, M, Answer = 11;
char map[11][11], copyMap[11][11];
int dir[11] = { 0, };
int sRed[2], sBlue[2], nRed[2], nBlue[2];

void print_map() {
	cout << "MAp" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << copyMap[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void copy_map() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			copyMap[i][j] = map[i][j];
		}
	}
	nRed[0] = sRed[0], nRed[1] = sRed[1];
	nBlue[0] = sBlue[0], nBlue[1] = sBlue[1];
}

int moveBall (int d, int sX, int sY, int color) {
	int nX, nY, retFlag = 0;
	copyMap[sX][sY] = '.';
	switch (d) {
	case 1:
		nX = sX, nY = sY;
		for (nY = sY; nY >= 0; nY--) {
			if (copyMap[nX][nY] == '#' || copyMap[nX][nY] == 'B' || copyMap[nX][nY] == 'R') {
				nY++;
				break;
			}
			else if (copyMap[nX][nY] == 'O') {
				retFlag = -1;
				break;
			}
		}
		if (sX == nX && sY == nY) {
			if (color == 0) copyMap[nX][nY] = 'R';
			else copyMap[nX][nY] = 'B';
			retFlag = 0;
		}
		else if (retFlag == -1) {
			if(color == 0) nRed[0] = nX, nRed[1] = nY;
			else nBlue[0] = nX, nBlue[1] = nY;
		}
		else {
			if (color == 0) nRed[0] = nX, nRed[1] = nY;
			else nBlue[0] = nX, nBlue[1] = nY;
			if (color == 0) copyMap[nX][nY] = 'R';
			else copyMap[nX][nY] = 'B';
			retFlag = 1;
		}
		break;
	case 2:
		nX = sX, nY = sY;
		for (nY = sY; nY < M; nY++) {
			if (copyMap[nX][nY] == '#' || copyMap[nX][nY] == 'B' || copyMap[nX][nY] == 'R') {
				nY--;
				break;
			}
			else if (copyMap[nX][nY] == 'O') {
				retFlag = -1;
				break;
			}
		}
		if (sX == nX && sY == nY) {
			if (color == 0) copyMap[nX][nY] = 'R';
			else copyMap[nX][nY] = 'B';
			retFlag = 0;
		}
		else if (retFlag == -1) {
			if (color == 0) nRed[0] = nX, nRed[1] = nY;
			else nBlue[0] = nX, nBlue[1] = nY;
		}
		else {
			if (color == 0) nRed[0] = nX, nRed[1] = nY;
			else nBlue[0] = nX, nBlue[1] = nY;
			if (color == 0) copyMap[nX][nY] = 'R';
			else copyMap[nX][nY] = 'B';
			retFlag = 1;
		}
		break;
	case 3:
		nX = sX, nY = sY;
		for (nX = sX; nX >= 0; nX--) {
			if (copyMap[nX][nY] == '#' || copyMap[nX][nY] == 'B' || copyMap[nX][nY] == 'R') {
				nX++;
				break;
			}
			else if (copyMap[nX][nY] == 'O') {
				retFlag = -1;
				break;
			}
		}
		if (sX == nX && sY == nY) {
			if (color == 0) copyMap[nX][nY] = 'R';
			else copyMap[nX][nY] = 'B';
			retFlag = 0;
		}
		else if (retFlag == -1) {
			if (color == 0) nRed[0] = nX, nRed[1] = nY;
			else nBlue[0] = nX, nBlue[1] = nY;
		}
		else {
			if (color == 0) nRed[0] = nX, nRed[1] = nY;
			else nBlue[0] = nX, nBlue[1] = nY;
			if (color == 0) copyMap[nX][nY] = 'R';
			else copyMap[nX][nY] = 'B';
			retFlag = 1;
		}
		break;
	case 4:
		nX = sX, nY = sY;
		for (nX = sX; nX < N; nX++) {
			if (copyMap[nX][nY] == '#' || copyMap[nX][nY] == 'B' || copyMap[nX][nY] == 'R') {
				nX--;
				break;
			}
			else if (copyMap[nX][nY] == 'O') {
				retFlag = -1;
				break;
			}
		}
		if (sX == nX && sY == nY) {
			if (color == 0) copyMap[nX][nY] = 'R';
			else copyMap[nX][nY] = 'B';
			retFlag = 0;
		}
		else if (retFlag == -1) {
			if (color == 0) nRed[0] = nX, nRed[1] = nY;
			else nBlue[0] = nX, nBlue[1] = nY;
		}
		else {
			if (color == 0) nRed[0] = nX, nRed[1] = nY;
			else nBlue[0] = nX, nBlue[1] = nY;
			if (color == 0) copyMap[nX][nY] = 'R';
			else copyMap[nX][nY] = 'B';
			retFlag = 1;
		}
		break;
	}
	return retFlag;
}

int simulation(int time) {
	if (time + 1 >= Answer) return 1;
	int d, rFlag = 0, bFlag = 0;
	d = dir[time];
	switch (d) {
	case 1:
		if (nRed[1] < nBlue[1]) {
			rFlag = moveBall(d, nRed[0], nRed[1], 0);
			bFlag = moveBall(d, nBlue[0], nBlue[1], 1);
		}
		else {
			bFlag = moveBall(d, nBlue[0], nBlue[1], 1);
			rFlag = moveBall(d, nRed[0], nRed[1], 0);
		}
		break;
	case 2:
		if (nRed[1] > nBlue[1]) {
			rFlag = moveBall(d, nRed[0], nRed[1], 0);
			bFlag = moveBall(d, nBlue[0], nBlue[1], 1);
		}
		else {
			bFlag = moveBall(d, nBlue[0], nBlue[1], 1);
			rFlag = moveBall(d, nRed[0], nRed[1], 0);
		}
		break;
	case 3:
		if (nRed[0] < nBlue[0]) {
			rFlag = moveBall(d, nRed[0], nRed[1], 0);
			bFlag = moveBall(d, nBlue[0], nBlue[1], 1);
		}
		else {
			bFlag = moveBall(d, nBlue[0], nBlue[1], 1);
			rFlag = moveBall(d, nRed[0], nRed[1], 0);
		}
		break;
	case 4:
		if (nRed[0] > nBlue[0]) {
			rFlag = moveBall(d, nRed[0], nRed[1], 0);
			bFlag = moveBall(d, nBlue[0], nBlue[1], 1);
		}
		else {
			bFlag = moveBall(d, nBlue[0], nBlue[1], 1);
			rFlag = moveBall(d, nRed[0], nRed[1], 0);
		}
		break;
	}

	if (rFlag == -1) {
		if (bFlag == -1) return 1;
		else {
			Answer = time + 1;
			return 1;
		}
	}
	else if (bFlag == -1) return 1;
	else if(rFlag ==0 && bFlag ==0) return 1;
	else return 0;
}

void DFS(int cnt) {
	if (cnt >= 10) {
		int breakFlag = 0;
		copy_map();
		/*
		for (int i = 0; i < 10; i++) {
			cout << dir[i] << ' ';
		}
		cout << endl;
		if (dir[0] == 1 && dir[1] == 4 && dir[2] == 2 && dir[3] == 4)
			cout << "찾음" << endl;
		*/
		for (int i = 0; i < 10; i++) {
			breakFlag =simulation(i);
			//print_map();
			if (breakFlag == 1) break;
		}
		return;
	}

	int sdir = dir[cnt - 1];
	if (sdir == 1 || sdir == 2) {
		for (int d = 3; d <= 4; d++) {
			dir[cnt] = d;
			DFS(cnt + 1);
		}
	}
	else if (sdir == 3 || sdir == 4) {
		for (int d = 1; d <= 2; d++) {
			dir[cnt] = d;
			DFS(cnt + 1);
		}
	}
}

void Solution() {
	for (int d = 1; d <= 4; d++) {
		dir[0] = d;
		DFS(1);
	}
}

void Input() {
	cin >> N >> M;

	string str;

	for (int i = 0; i < N; i++) {
		cin >> str;
		for (int j = 0; j < M; j++) {
			map[i][j] = str.at(j);
			if (map[i][j] == 'R') {
				sRed[0] = i, sRed[1] = j;
			}
			else if (map[i][j] == 'B') {
				sBlue[0] = i, sBlue[1] = j;
			}
		}
	}
	/*
	scanf("%c");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%c", &map[i][j]);
			if (map[i][j] == 'R') {
				sRed[0] = i, sRed[1] = j;
			}
			else if (map[i][j] == 'B') {
				sBlue[0] = i, sBlue[1] = j;
			}
		}
		scanf("%c");
	}
	*/
	/*
	cout << "Map" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	*/
}


int main(void) {
	Input();
	Solution();
	if (Answer == 11) Answer = -1;
	cout << Answer << endl;
	return 0;
}