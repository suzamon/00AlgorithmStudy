#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int N, M, K, Answer = 0;
int map[21][21];
int command[1001];

int dicePos[2]; //주사위 좌표;
int dice[4][3] = { 0, }; //주사위 상태;

int dx[5] = { 0, 0, 0, -1, 1 }; //동, 서, 북, 남
int dy[5] = { 0, 1, -1, 0, 0 };

void Rot_dice(int dir) {
	int tmp;
	switch (dir) {
	case 1:
		tmp = dice[1][0];
		dice[1][0] = dice[3][1];
		dice[3][1] = dice[1][2];
		dice[1][2] = dice[1][1];
		dice[1][1] = tmp;
		break;
	case 2:
		tmp = dice[1][0];
		dice[1][0] = dice[1][1];
		dice[1][1] = dice[1][2];
		dice[1][2] = dice[3][1];
		dice[3][1] = tmp;
		break;
	case 3:
		tmp = dice[0][1];
		for (int i = 0; i < 3; i++) {
			dice[i][1] = dice[i + 1][1];
		}
		dice[3][1] = tmp;
		break;
	case 4:
		tmp = dice[3][1];
		for (int i = 3; i > 0; i--) {
			dice[i][1] = dice[i - 1][1];
		}
		dice[0][1] = tmp;
		break;
	}
}

void Move(int dir) {
	int startX, startY, nextX, nextY, bottom, top;

	startX = dicePos[0];
	startY = dicePos[1];
	nextX = startX + dx[dir];
	nextY = startY + dy[dir];
	if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) {
		return;
	}
	else {
		Rot_dice(dir);//주사위 회전
		top = dice[1][1];
		bottom = dice[3][1];
		if (map[nextX][nextY] == 0) {
			map[nextX][nextY] = bottom;
		}
		else {
			dice[3][1] = map[nextX][nextY];
			map[nextX][nextY] = 0;
		}
		dicePos[0] = nextX;
		dicePos[1] = nextY;
		cout << top << endl;
		return;
	}
}
void Solve() {
	for (int i = 0; i < K; i++) {
		Move(command[i]);
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
	for (int i = 0; i < K; i++) {
		cin >> command[i];
	}
	return;
}

int main(void) {

	Input();
	Solve();



	/*
	dice[0][1] = 2;
	dice[1][1] = 1;
	dice[2][1] = 5;
	dice[3][1] = 6;
	dice[1][0] = 4;
	dice[1][2] = 3;
	Rot_dice(4);
	cout << "4번 회전" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			cout << dice[i][j] << ' ';
		}
		cout << endl;
	}
	*/

	return 0;
}