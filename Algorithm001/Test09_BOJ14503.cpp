/*\
문제
로봇 청소기가 주어졌을 때, 청소하는 영역의 개수를 구하는 프로그램을 작성하시오.

로봇 청소기가 있는 장소는 N×M 크기의 직사각형으로 나타낼 수 있으며,
1×1크기의 정사각형 칸으로 나누어져 있다. 각각의 칸은 벽 또는 빈 칸이다.
청소기는 바라보는 방향이 있으며, 이 방향은 동, 서, 남, 북중 하나이다.
지도의 북쪽에서부터 r번째, 서쪽에서부터 c번째로 위치한 칸은 (r, c)로 나타낼 수 있다.

로봇 청소기는 다음과 같이 작동한다.

1. 현재 위치를 청소한다.
2. 현재 위치에서 다음을 반복하면서 인접한 칸을 탐색한다.
	a. 현재 위치의 바로 왼쪽에 아직 청소하지 않은 빈 공간이 존재한다면,
	   왼쪽 방향으로 회전한 다음 한 칸을 전진하고 1번으로 돌아간다.
	   그렇지 않을 경우, 왼쪽 방향으로 회전한다. 이때, 왼쪽은 현재 바라보는 방향을 기준으로 한다.
	b. 1번으로 돌아가거나 후진하지 않고 2a번 단계가 연속으로 네 번 실행되었을 경우,
		바로 뒤쪽이 벽이라면 작동을 멈춘다. 그렇지 않다면 한 칸 후진한다.

입력
첫째 줄에 세로 크기 N과 가로 크기 M이 주어진다. (3 ≤ N, M ≤ 50)
둘째 줄에 로봇 청소기가 있는 칸의 좌표 (r, c)와 바라보는 방향 d가 주어진다.
d가 0인 경우에는 북쪽을, 1인 경우에는 동쪽을, 2인 경우에는 남쪽을,
3인 경우에는 서쪽을 바라보고 있는 것이다.

셋째 줄부터 N개의 줄에 장소의 상태가 북쪽부터 남쪽 순서대로,
각 줄은 서쪽부터 동쪽 순서대로 주어진다.
빈 칸은 0, 벽은 1로 주어진다. 지도의 첫 행, 마지막 행, 첫 열, 마지막 열에 있는 모든 칸은 벽이다.
로봇 청소기가 있는 칸의 상태는 항상 빈 칸이다.

출력
로봇 청소기가 청소하는 칸의 개수를 출력한다.

N, M, Answer
int map[51][51] = {0, }, visited[51][51] ={0, };
int dx[4], dy[4] -> 0: 북, 1: 동, 2: 남, 3: 서
int robot[3] -> x, y, dir


Input()
	N, M, robot[3], map[N][M]

Solution()
	int sX, sY, sD, nX, nY, nD, flag = 0;
	int clearCnt = 0;
	while(1){
	flag = 0;
	sX = robot[0], sY = robot[1], sD = robot[2];
	nD = sD;
	clearCnt++;
	for(int i=0; i<4; i++){
	nD = change_dir(nD);
	nX = sX + dx[d], nY = sY + dy[d];
	if(!inRange(nX, nY)) continue;
	if(map[nX][nY] == 0 && visited[nX][nY] == 0){
	robot[0] = nX, robot[1] = nY, robot[2] = nD;
	visited[nX][nY] = 1;
	}
	}
	if(sX == robot[0] && sY == robot[1] && sD == robot[2]){
	nX = sX - dx[sD], nY = sY - dy[sD];
	if(!inRange(nX, nY)) break;
	if(map[nX][nY] == 1) break;
	}
	}

int change_dir(int d){
	int retDir = d - 1;
	if(retDir < 0) retDir = 3;
	retunr retDir;
}


*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int N, M, Answer = 0;
int map[51][51] = { 0, }, visited[51][51] = { 0, };
int robot[3];

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0 ,-1 };

void print_info() {
	cout << "로봇 위치: " << robot[0] << ", " << robot[1] << ", 방향: " << robot[2] << endl;
	cout << "맵" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << "방문 맵" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << visited[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

bool inRange(int xx, int yy) {
	if (xx >= 0 && xx < N && yy >= 0 && yy < M) return true;
	return false;
}

int change_dir(int d) {
	int retDir = d - 1;
	if (retDir < 0) retDir = 3;
	return retDir;
}

int  Solution() {
	int sX, sY, sD, nX, nY, nD;
	int clearCnt = 0;

	clearCnt++;
	visited[robot[0]][robot[1]] = 1;
	while (1) {
		sX = robot[0], sY = robot[1], sD = robot[2];
		nD = sD;
		for (int i = 0; i < 4; i++) {
			nD = change_dir(nD);
			nX = sX + dx[nD], nY = sY + dy[nD];
			if (!inRange(nX, nY)) continue;
			if (map[nX][nY] == 0 && visited[nX][nY] == 0) {
				robot[0] = nX, robot[1] = nY, robot[2] = nD;
				visited[nX][nY] = 1;
				clearCnt++;
				break;
			}
		}
		if (sX == robot[0] && sY == robot[1] && sD == robot[2]) {
			nX = sX - dx[sD], nY = sY - dy[sD];
			if (!inRange(nX, nY)) break;

			if (map[nX][nY] == 1) break;
			else if (map[nX][nY] == 0) {
				robot[0] = nX, robot[1] = nY, robot[2] = sD;
			}
		}

		//print_info();
	}

	return clearCnt;
}

void Input() {
	cin >> N >> M;
	for (int i = 0; i < 3; i++) {
		cin >> robot[i];
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
}


int main(void) {
	Input();
	Answer = Solution();
	cout << Answer << endl;
	return 0;
}