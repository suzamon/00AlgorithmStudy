/*
크기가 N×M인 지도, 지도의 오른쪽은 동쪽, 위쪽은 북쪽
도의 좌표는 (r, c)로 나타내며, r는 북쪽으로부터 떨어진 칸의 개수, c는 서쪽으로부터 떨어진 칸의 개수
주사위는 지도 위에 윗 면이 1이고, 동쪽을 바라보는 방향이 3인 상태로 놓여져 있으며, 놓여져 있는 곳의 좌표는 (x, y) 이다.
가장 처음에 주사위에는 모든 면에 0이 적혀져 있다.

지도의 각 칸에는 정수가 하나씩 쓰여져 있다.
주사위를 굴렸을 때, 이동한 칸에 쓰여 있는 수가 0이면, 주사위의 바닥면에 쓰여 있는 수가 칸에 복사,
0이 아닌 경우에는 칸에 쓰여 있는 수가 주사위의 바닥면으로 복사되며, 칸에 쓰여 있는 수는 0이 된다.

주사위를 놓은 곳의 좌표와 이동시키는 명령이 주어졌을 때,
주사위가 이동했을 때 마다 상단에 쓰여 있는 값을 구하는 프로그램을 작성

주사위는 지도의 바깥으로 이동시킬 수 없다.
만약 바깥으로 이동시키려고 하는 경우에는 해당 명령을 무시해야 하며, 출력도 하면 안 된다.

첫째 줄에 지도의 세로 크기 N, 가로 크기 M (1 ≤ N, M ≤ 20),
주사위를 놓은 곳의 좌표 x, y(0 ≤ x ≤ N-1, 0 ≤ y ≤ M-1), 그리고 명령의 개수 K (1 ≤ K ≤ 1,000)가 주어진다.

둘째 줄부터 N개의 줄에 지도에 쓰여 있는 수가 북쪽부터 남쪽으로,
각 줄은 서쪽부터 동쪽 순서대로 주어진다. 주사위를 놓은 칸에 쓰여 있는 수는 항상 0이다.
지도의 각 칸에 쓰여 있는 수는 10 미만의 자연수 또는 0이다.

마지막 줄에는 이동하는 명령이 순서대로 주어진다. 동쪽은 1, 서쪽은 2, 북쪽은 3, 남쪽은 4로 주어진다.

이동할 때마다 주사위의 윗 면에 쓰여 있는 수를 출력한다.
만약 바깥으로 이동시키려고 하는 경우에는 해당 명령을 무시해야 하며, 출력도 하면 안 된다.

<dice Map> => 이동할 때마다 6번 출력 & 1번 위치 값 변함
0 2 0
4 1 3
0 5 0
0 6 0

1) 동
0 2 0
1 3 6
0 5 0
0 4 0

2) 서
0 2 0
6 4 1
0 5 0
0 3 0

3) 북
0 6 0
4 2 3
0 1 0
0 5 0

4) 남
0 1 0
4 5 3
0 6 0
0 2 0

이동 -> deque로 구현

1. Input
	N, M, dice[2], K
	Map[N][M]
	command[K]

2. Solution
	1. 1~K만큼 진행
	2) 먼저 dice x,y 이동 -> 맵 밖이면 변경X
	3-1-1) 이동 명령어가 유효하면 dice 맵 변경
	3-1-2) map[diceX][diceY] == 0이면 dice 값 복사, 아니면 map 값 복사 & 업데이트
	3-2) 이동 명령어 무효 -> 그대로
	4) diceMap[3][2] 출력
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