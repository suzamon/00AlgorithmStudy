/*
1'21''42'''
크기가 N×M인 지도가 존재한다. 지도의 오른쪽은 동쪽, 위쪽은 북쪽이다. 지도의 좌표는 (r, c)로 나타내며,
r는 북쪽으로부터 떨어진 칸의 개수, c는 서쪽으로부터 떨어진 칸의 개수이다.
가장 왼쪽 위에 있는 칸의 좌표는 (1, 1)이고, 가장 오른쪽 아래에 있는 칸의 좌표는 (N, M)이다.
이 지도의 위에 주사위가 하나 놓여져 있으며, 주사위의 각 면에는 1보다 크거나 같고, 6보다 작거나 같은 정수가 하나씩 있다.
주사위 한 면의 크기와 지도 한 칸의 크기는 같고, 주사위의 전개도는 아래와 같다.

  2
4 1 3
  5
  6

주사위는 지도 위에 윗 면이 1이고, 동쪽을 바라보는 방향이 3인 상태로 놓여져 있으며,
놓여져 있는 곳의 좌표는 (1, 1) 이다. 지도의 각 칸에도 정수가 하나씩 있다. 가장 처음에 주사위의 이동 방향은 동쪽이다.
주사위의 이동 한 번은 다음과 같은 방식으로 이루어진다.

1. 주사위가 이동 방향으로 한 칸 굴러간다. 만약, 이동 방향에 칸이 없다면, 이동 방향을 반대로 한 다음 한 칸 굴러간다.
2. 주사위가 도착한 칸 (x, y)에 대한 점수를 획득한다.
3. 주사위의 아랫면에 있는 정수 A와 주사위가 있는 칸 (x, y)에 있는 정수 B를 비교해 이동 방향을 결정한다.
	- A > B인 경우 이동 방향을 90도 시계 방향으로 회전시킨다.
	- A < B인 경우 이동 방향을 90도 반시계 방향으로 회전시킨다.
	- A = B인 경우 이동 방향에 변화는 없다.

칸 (x, y)에 대한 점수는 다음과 같이 구할 수 있다. (x, y)에 있는 정수를 B라고 했을때,
(x, y)에서 동서남북 방향으로 연속해서 이동할 수 있는 칸의 수 C를 모두 구한다.
이때 이동할 수 있는 칸에는 모두 정수 B가 있어야 한다. 여기서 점수는 B와 C를 곱한 값이다.
보드의 크기와 각 칸에 있는 정수, 주사위의 이동 횟수 K가 주어졌을때, 각 이동에서 획득하는 점수의 합을 구해보자.

이 문제의 예제 1부터 7은 같은 지도에서 이동하는 횟수만 증가시키는 방식으로 구성되어 있다.
예제 8은 같은 지도에서 이동하는 횟수를 매우 크게 만들었다.

입력
첫째 줄에 지도의 세로 크기 N, 가로 크기 M (2 ≤ N, M ≤ 20), 그리고 이동하는 횟수 K (1 ≤ K ≤ 1,000)가 주어진다.
둘째 줄부터 N개의 줄에 지도에 쓰여 있는 수가 북쪽부터 남쪽으로, 각 줄은 서쪽부터 동쪽 순서대로 주어진다.
지도의 각 칸에 쓰여 있는 수는 10 미만의 자연수이다.

출력
첫째 줄에 각 이동에서 획득하는 점수의 합을 출력한다.

(1,1) ~ (N, M), 첫 위치 (1,1), 첫 이동방향 동쪽
N, M, K, dice[3], map[21][21], diceMap[5][4], visited[21][21];
int dx[4], dy[4] -> 동, 남, 서, 북

1. Input()
	N, M, K, map[N][M], dice[0]=dice[1] = 1, dice[2] = 1;
2. Soltion()
	1) int time
	2) for(time =1; time<=K; time++)
	3) moveDice()
		1) int sX, sY, dir, nX, nY, score;
		2) sX = dice[0], sY = dice[1], dir = dice[2];
		3) nX = sX + dx[d], nY = sY + dy[dir];
		4)if(!inRange(nX, nY)) dir = change_dir(dir, 0), dice[2] = dir, nX = sX + dx[d], nY = sY + dy[dir];
		6) visied[nX][nY] = 1;
		7) DFS(nX, nY, 1);
		8) score = find_cnt(); -> visited 돌면서 '1'인 갯수 반환 & reset
		9) score = map[nX][nY] * score;
		10) Answer = Answer + score;
		11) dice[0]= nX, dice[1] = nY;
		11) change_diceMap(int dir)
		12) if(diceMap[2][2]  > map[nX][nY]) dice[2] = change_dir(dir, 1)
		13) else if((diceMap[2][2]  < map[nX][nY]) dice [2] = change_dir(dir, 2)


	4) void DFS(int x, int y, int cnt)
		1) int sX, sY, sNum, nX, nY;
		2) sX= x, sY = y, sNum = map[x][y], nCnt = cnt;
		3) for(int d=1; d<=4; d++){
		4) nX = sX + dx[d], nY = sY + dy[d];
		4) if(!inRange(nX, nY)) continue;
		5) if(map[nX][nY] == sNum && visited[nX][nY] == 0){
		6) visited[nX][nY] = 1;
		7) DFS(nX, nY, cnt+1);}



*change_dir(int dir, int s) -> s = 0, 반대 chagne, s=1 이면 시계 90도, s=2이면 반시계 90도
	0) int nDir;
	1) if(s==0) -> if(dir==3||dir==4) nDir = dir-2;  else nDir = dri+2;
	2) else if(s==1) -> if(dir < 4) nDir = dir +1; else nDir = 1;
	3) else if(s==2) -> if(dir > 1) nDir = dir - 1; else nDir = 4;
	4) return nDir;

*diceMap(int dir)
	1) queue <int> q;
	2) switch(dir)
	3) case 1: for(int i=2; i<4; i++) q.push(diceMap[2][i]);
	4)	q.push(diceMap[2][1]);
	5)	for(int i=1; i<4; i++) diceMap[2][i] = q.front() & q.pop();
	6) case 2: for(int i=2; i<5; i++) q.push(diceMap[i][2])
		q.push(diceMap[1][2]);
		for(int i=1; i<5; i++) diceMap[i][2] = q.front() & q.pop();
	7) case 3: q.push(diceMap[2][3])
	8)	for(int i=1; i<3; i++) q.push(diceMap[2][i]));
	9)	for(int i=1; i<4; i++) diceMap[2][i] = q.front() & q.pop();
	10) case 4: q.push(diceMap[4][2]);
		for(int i=1; i<4; i++) q.push(diceMap[i][2]);
		for(int i=1; i<5; i++) diceMap[i][2] = q.front() & q.pop();

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
int dice[3], map[21][21];
int visited[21][21] = { 0, };
int diceMap[5][4] = { {0, 0, 0, 0}, {0, 0, 2, 0}, {0, 4, 1, 3}, {0, 0, 5, 0}, {0, 0, 6, 0} };

int dx[5] = { 0, 0, 1, 0, -1 };
int dy[5] = { 0, 1, 0, -1, 0 };

void print_info() {
	cout << "주사위 정보" << endl;
	cout << '(' << dice[0] << ", " << dice[1] << ")에 위치, 방향: " << dice[2] << endl;
	cout << "Score: " << Answer << endl;
	cout << "주사위 맵" << endl;
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 3; j++) {
			cout << diceMap[i][j] << ' ';
		}
		cout << endl;
	}
}

bool inRange(int x, int y) {
	if (x<1 || x>N || y<1 || y>M) return false;
	return true;
}
int change_dir(int dir, int s) {
	int nDir;
	if (s == 0) {
		if (dir == 3 || dir == 4)nDir = dir - 2;
		else nDir = dir + 2;
	}
	else if (s == 1) {
		if (dir < 4) nDir = dir + 1;
		else nDir = 1;
	}
	else if (s == 2) {
		if (dir > 1) nDir = dir - 1;
		else nDir = 4;
	}

	return nDir;
}

int find_score() {
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (visited[i][j] == 1) {
				cnt++;
				visited[i][j] = 0;
			}
		}
	}
	return cnt;
}

void DFS(int x, int y, int sNum) {
	int sX, sY, nX, nY;
	sX = x, sY = y;
	for (int d = 1; d <= 4; d++) {
		nX = sX + dx[d], nY = sY + dy[d];
		if (!inRange(nX, nY)) continue;
		if (map[nX][nY] == sNum && visited[nX][nY] == 0) {
			visited[nX][nY] = 1;
			DFS(nX, nY, sNum);
		}
	}
}

void change_diceMap(int d) {
	queue <int> q;
	switch (d) {
	case 1:
		q.push(diceMap[4][2]);
		for (int i = 1; i < 4; i++) q.push(diceMap[2][i]);
		for (int i = 1; i < 4; i++) {
			diceMap[2][i] = q.front();
			q.pop();
		}
		diceMap[4][2] = q.front();
		q.pop();
		break;
	case 2:
		q.push(diceMap[4][2]);
		for (int i = 1; i < 4; i++) q.push(diceMap[i][2]);
		for (int i = 1; i < 5; i++) {
			diceMap[i][2] = q.front();
			q.pop();
		}
		break;
	case 3:
		for (int i = 2; i <= 3; i++) q.push(diceMap[2][i]);
		q.push(diceMap[4][2]);
		q.push(diceMap[2][1]);
		for (int i = 1; i < 4; i++) {
			diceMap[2][i] = q.front();
			q.pop();
		}
		diceMap[4][2] = q.front();
		q.pop();
		break;
	case 4:
		for (int i = 2; i < 5; i++) q.push(diceMap[i][2]);
		q.push(diceMap[1][2]);
		for (int i = 1; i < 5; i++) {
			diceMap[i][2] = q.front();
			q.pop();
		}
		break;
	}
}

void move_dice() {
	int sX, sY, dir, nX, nY, score;
	sX = dice[0], sY = dice[1], dir = dice[2];
	nX = sX + dx[dir], nY = sY + dy[dir];
	if (!inRange(nX, nY)) {
		dir = change_dir(dir, 0);
		dice[2] = dir;
		nX = sX + dx[dir], nY = sY + dy[dir];
	}

	visited[nX][nY] = 1;
	DFS(nX, nY, map[nX][nY]);

	score = find_score() * map[nX][nY];
	Answer = Answer + score;

	dice[0] = nX, dice[1] = nY;
	change_diceMap(dir);

	if (diceMap[4][2] > map[nX][nY]) dice[2] = change_dir(dir, 1);
	else if (diceMap[4][2] < map[nX][nY]) dice[2] = change_dir(dir, 2);
}

void Solution() {
	int time;
	for (time = 1; time <= K; time++) {
		move_dice();
		//cout << time << "초 후" << endl;
		//print_info();
	}
	cout << Answer << endl;
}

void Input() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j];
		}
	}
	dice[0] = 1;
	dice[1] = 1;
	dice[2] = 1;
}

int main(void) {
	Input();
	Solution();
	return 0;
}