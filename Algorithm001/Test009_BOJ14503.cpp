/*
로봇 청소기가 주어졌을 때, 청소하는 영역의 개수를 구하는 프로그램을 작성하시오.

로봇 청소기가 있는 장소는 N×M 크기의 직사각형으로 나타낼 수 있으며,
1×1크기의 정사각형 칸으로 나누어져 있다. 각각의 칸은 벽 또는 빈 칸이다.
청소기는 바라보는 방향이 있으며, 이 방향은 동, 서, 남, 북중 하나이다.
지도의 각 칸은 (r, c)로 나타낼 수 있고, r은 북쪽으로부터 떨어진 칸의 개수, c는 서쪽으로 부터 떨어진 칸의 개수이다.

1. 현재 위치를 청소한다.
2. 현재 위치에서 현재 방향을 기준으로 왼쪽 방향부터 차례대로 인접한 칸을 탐색한다.
	왼쪽 방향에 아직 청소하지 않은 공간이 존재한다면, 그 방향으로 회전한 다음 한 칸을 전진하고 1번부터 진행한다.
	왼쪽 방향에 청소할 공간이 없다면, 그 방향으로 회전하고 2번으로 돌아간다.
	네 방향 모두 청소가 이미 되어있거나 벽인 경우에는, 바라보는 방향을 유지한 채로 한 칸 후진을 하고 2번으로 돌아간다.
	네 방향 모두 청소가 이미 되어있거나 벽이면서, 뒤쪽 방향이 벽이라 후진도 할 수 없는 경우에는 작동을 멈춘다.
	로봇 청소기는 이미 청소되어있는 칸을 또 청소하지 않으며, 벽을 통과할 수 없다.


첫째 줄에 세로 크기 N과 가로 크기 M이 주어진다. (3 ≤ N, M ≤ 50)
둘째 줄에 로봇 청소기가 있는 칸의 좌표 (r, c)와 바라보는 방향 d가 주어진다.
d가 0인 경우에는 북쪽을, 1인 경우에는 동쪽을, 2인 경우에는 남쪽을, 3인 경우에는 서쪽을 바라보고 있는 것이다.
셋째 줄부터 N개의 줄에 장소의 상태가 북쪽부터 남쪽 순서대로, 각 줄은 서쪽부터 동쪽 순서대로 주어진다.
빈 칸은 0, 벽은 1로 주어진다. 지도의 첫 행, 마지막 행, 첫 열, 마지막 열에 있는 모든 칸은 벽이다.
로봇 청소기가 있는 칸의 상태는 항상 빈 칸이다.

로봇 청소기가 청소하는 칸의 개수를 출력한다.

dx, dy -> 북, 동, 남, 서

1. Input()
	N, M, map[N][M], robot[3]

2. Simualtion()
	1. 현재 위치 청소(robotCnt++)
	2. 왼쪽 회전 후 탐색 -> 4번 반복
	3. 4번 반복해도 없으면 뒤로 한칸 이동 -> 벽이면 종료
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, M, Answer = 0;
int map[51][51];
int visited[51][51] = { 0, };
int robot[3];
int robotCnt;

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int rot_dir(int curDir) {
	if (curDir == 0) return 3;
	else return curDir - 1;
}

void Simulation() {
	int curX, curY, nextX, nextY;
	int nextDir, rotCnt;

	while (1) {
		//cout << robot[0] << ", " << robot[1] << "청소 완료" << endl;
		if (visited[robot[0]][robot[1]] == 0) robotCnt++;
		visited[robot[0]][robot[1]] = 1;

		curX = robot[0], curY = robot[1], nextDir = robot[2];
		rotCnt = 0;
		for (int i = 0; i < 4; i++) {
			nextDir = rot_dir(nextDir);
			nextX = curX + dx[nextDir];
			nextY = curY + dy[nextDir];
			if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) rotCnt++;
			else if (map[nextX][nextY] == 0 && visited[nextX][nextY] == 0) {
				robot[0] = nextX;
				robot[1] = nextY;
				robot[2] = nextDir;
				break;
			}
			else rotCnt++;
		}

		if (rotCnt == 4) {
			nextX = curX - dx[robot[2]];
			nextY = curY - dy[robot[2]];
			if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) break;
			else if (map[nextX][nextY] == 1) break;
			else {
				robot[0] = nextX;
				robot[1] = nextY;
				//robot[2] = nextDir;
			}
		}
	}

}

void Input() {
	cin >> N >> M;
	for (int i = 0; i < 3; i++) cin >> robot[i];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
	robotCnt = 0;
}

int main(void) {
	Input();
	Simulation();
	cout << robotCnt << endl;
	return 0;
}