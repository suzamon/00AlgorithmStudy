/*
문제
크기가 N×M인 지도가 존재한다. 지도의 오른쪽은 동쪽, 위쪽은 북쪽이다.
이 지도의 위에 주사위가 하나 놓여져 있으며, 주사위의 전개도는 아래와 같다.
 지도의 좌표는 (r, c)로 나타내며, r는 북쪽으로부터 떨어진 칸의 개수, c는 서쪽으로부터 떨어진 칸의 개수이다.

주사위는 지도 위에 윗 면이 1이고, 동쪽을 바라보는 방향이 3인 상태로 놓여져 있으며,
놓여져 있는 곳의 좌표는 (x, y) 이다. 가장 처음에 주사위에는 모든 면에 0이 적혀져 있다.

지도의 각 칸에는 정수가 하나씩 쓰여져 있다.
주사위를 굴렸을 때, 이동한 칸에 쓰여 있는 수가 0이면, 주사위의 바닥면에 쓰여 있는 수가 칸에 복사된다.
0이 아닌 경우에는 칸에 쓰여 있는 수가 주사위의 바닥면으로 복사되며, 칸에 쓰여 있는 수는 0이 된다.

주사위를 놓은 곳의 좌표와 이동시키는 명령이 주어졌을 때,
주사위가 이동했을 때 마다 상단에 쓰여 있는 값을 구하는 프로그램을 작성하시오.

주사위는 지도의 바깥으로 이동시킬 수 없다.
만약 바깥으로 이동시키려고 하는 경우에는 해당 명령을 무시해야 하며, 출력도 하면 안 된다.

입력
첫째 줄에 지도의 세로 크기 N, 가로 크기 M (1 ≤ N, M ≤ 20),
주사위를 놓은 곳의 좌표 x, y(0 ≤ x ≤ N-1, 0 ≤ y ≤ M-1), 그리고 명령의 개수 K (1 ≤ K ≤ 1,000)가 주어진다.

둘째 줄부터 N개의 줄에 지도에 쓰여 있는 수가 북쪽부터 남쪽으로, 각 줄은 서쪽부터 동쪽 순서대로 주어진다.
주사위를 놓은 칸에 쓰여 있는 수는 항상 0이다. 지도의 각 칸에 쓰여 있는 수는 10 미만의 자연수 또는 0이다.

마지막 줄에는 이동하는 명령이 순서대로 주어진다. 동쪽은 1, 서쪽은 2, 북쪽은 3, 남쪽은 4로 주어진다.

출력
이동할 때마다 주사위의 윗 면에 쓰여 있는 수를 출력한다.
만약 바깥으로 이동시키려고 하는 경우에는 해당 명령을 무시해야 하며, 출력도 하면 안 된다.


N, M, K,
map[21][21], dicePos[2];
int diceMap[4][3];
deque <int> com;

int dx[5], dy[5] -> 동쪽은 1, 서쪽은 2, 북쪽은 3, 남쪽은 4

1. Input()
	N, M, dicePos[2], K, map[N][M], com

2. Solution()
	int dir;
	while(!com.empty()){
	dir = com.front(), com.pop_front();
	move_dice(dir)
	print_dice_up()
	}

* void move_dice(dir)
	int nX, nY;
	nX = dicePos[0] + dx[dir];
	nY = dicePos[1] + dy[dir];
	if(!inRange(nX, nY)) return;
	change_diceMap(dir);
	int tmp;
	if(map[nX][nY] == 	0) {
	map[nX][nY] = diceMap[1][1];
	return;
	}
	diceMap[1][1] = map[nX][nY];
	map[nX][nY] = 0;
	return;

*void change_diceMap(int dir)
	deque <int> tmp;
	switch(dir){
	case 1:
		for(int i=1; i<=2; i++) tmp.push_back(diceMap[1][i])
		tmp.push_back(diceMap[3][1])
		tmp.push_back(diceMap[1][0]);
		for(int i=0; i<=2; i++) {
		diceMap[1][i] = tmp.front();
		tmp.pop_front();
		}
		diceMap[3][1] = tmp.front();
		tmp.pop_front();
		break;
	case 2:
		tmp.push_back(diceMap[3][1])
		for(int i=0; i<=2; i++) tmp.push_back(diceMap[1][i])
		for(int i=0; i<=2; i++) {
		diceMap[1][i] = tmp.front();
		tmp.pop_front();
		}
		diceMap[3][1] = tmp.front();
		tmp.pop_front();
		break;
	case 3:
		tmp.push_back(diceMap[3][1]);
		for(int i=0; i<=2; i++) tmp.push_back(diceMap[i][1]);
		for(int i=0; i<=3; i++){
		diceMap[i][1] = tmp.front();
		tmp.pop_front();
		}
		break;
	case 4:
		for(int i=1; i<=3; i++) tmp.push_back(diceMap[i][1]);
		tmp.push_back(diceMap[0][1]);
		for(int i=0; i<=3; i++){
		diceMap[i][1] = tmp.front();
		tmp.pop_front();
		}
		break;
	}
	return;
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int N, M, K, Answer = 0;
int map[21][21], dicePos[2];
int diceMap[4][3] = { 0, };

deque <int> com;

int dx[5] = { 0, 0, 0, -1, 1 };
int dy[5] = { 0, 1, -1, 0, 0 };

void change_diceMap(int dir){
	deque <int> tmp;
	switch (dir) {
	case 1:
		for (int i = 1; i <= 2; i++) tmp.push_back(diceMap[1][i]);
		tmp.push_back(diceMap[3][1]);
		tmp.push_back(diceMap[1][0]);
		for (int i = 0; i <= 2; i++) {
			diceMap[1][i] = tmp.front();
			tmp.pop_front();
		}
		diceMap[3][1] = tmp.front();
		tmp.pop_front();
		break;
	case 2:
		tmp.push_back(diceMap[3][1]);
		for (int i = 0; i <= 2; i++) tmp.push_back(diceMap[1][i]);
		for (int i = 0; i <= 2; i++) {
			diceMap[1][i] = tmp.front();
			tmp.pop_front();
		}
		diceMap[3][1] = tmp.front();
		tmp.pop_front();
		break;
	case 3:
		tmp.push_back(diceMap[3][1]);
		for (int i = 0; i <= 2; i++) tmp.push_back(diceMap[i][1]);
		for (int i = 0; i <= 3; i++) {
			diceMap[i][1] = tmp.front();
			tmp.pop_front();
		}
		break;
	case 4:
		for (int i = 1; i <= 3; i++) tmp.push_back(diceMap[i][1]);
		tmp.push_back(diceMap[0][1]);
		for (int i = 0; i <= 3; i++) {
			diceMap[i][1] = tmp.front();
			tmp.pop_front();
		}
		break;
	}
	return;

}

bool inRange(int xx, int yy) {
	if (xx >= 0 && xx < N && yy >= 0 && yy < M) return true;
	return false;
}

int move_dice(int dir) {
	int nX, nY;
	nX = dicePos[0] + dx[dir];
	nY = dicePos[1] + dy[dir];
	if (!inRange(nX, nY)) return 1;
	dicePos[0] = nX, dicePos[1] = nY;
	change_diceMap(dir);
	int tmp;
	if (map[nX][nY] == 0) {
		map[nX][nY] = diceMap[1][1];
	}
	else {
		diceMap[1][1] = map[nX][nY];
		map[nX][nY] = 0;
	}
	return 0;

}

void print_dice_up() {
	cout << diceMap[3][1] << endl;
}

void Solution() {
	int dir, flag = 0;
	while (!com.empty()) {
		dir = com.front(), com.pop_front();
		flag = move_dice(dir);
		if (flag == 0) print_dice_up();
	}
}

void Input() {
	cin >> N >> M;
	for (int i = 0; i < 2; i++) {
		cin >> dicePos[i];
	}
	cin >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	int tmp;
	for (int i = 0; i < K; i++) {
		cin >> tmp;
		com.push_back(tmp);
	}
}


int main(void) {
	Input();
	Solution();
	return 0;
}