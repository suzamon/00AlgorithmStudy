/*
1'21''42'''
ũ�Ⱑ N��M�� ������ �����Ѵ�. ������ �������� ����, ������ �����̴�. ������ ��ǥ�� (r, c)�� ��Ÿ����,
r�� �������κ��� ������ ĭ�� ����, c�� �������κ��� ������ ĭ�� �����̴�.
���� ���� ���� �ִ� ĭ�� ��ǥ�� (1, 1)�̰�, ���� ������ �Ʒ��� �ִ� ĭ�� ��ǥ�� (N, M)�̴�.
�� ������ ���� �ֻ����� �ϳ� ������ ������, �ֻ����� �� �鿡�� 1���� ũ�ų� ����, 6���� �۰ų� ���� ������ �ϳ��� �ִ�.
�ֻ��� �� ���� ũ��� ���� �� ĭ�� ũ��� ����, �ֻ����� �������� �Ʒ��� ����.

  2
4 1 3
  5
  6

�ֻ����� ���� ���� �� ���� 1�̰�, ������ �ٶ󺸴� ������ 3�� ���·� ������ ������,
������ �ִ� ���� ��ǥ�� (1, 1) �̴�. ������ �� ĭ���� ������ �ϳ��� �ִ�. ���� ó���� �ֻ����� �̵� ������ �����̴�.
�ֻ����� �̵� �� ���� ������ ���� ������� �̷������.

1. �ֻ����� �̵� �������� �� ĭ ��������. ����, �̵� ���⿡ ĭ�� ���ٸ�, �̵� ������ �ݴ�� �� ���� �� ĭ ��������.
2. �ֻ����� ������ ĭ (x, y)�� ���� ������ ȹ���Ѵ�.
3. �ֻ����� �Ʒ��鿡 �ִ� ���� A�� �ֻ����� �ִ� ĭ (x, y)�� �ִ� ���� B�� ���� �̵� ������ �����Ѵ�.
	- A > B�� ��� �̵� ������ 90�� �ð� �������� ȸ����Ų��.
	- A < B�� ��� �̵� ������ 90�� �ݽð� �������� ȸ����Ų��.
	- A = B�� ��� �̵� ���⿡ ��ȭ�� ����.

ĭ (x, y)�� ���� ������ ������ ���� ���� �� �ִ�. (x, y)�� �ִ� ������ B��� ������,
(x, y)���� �������� �������� �����ؼ� �̵��� �� �ִ� ĭ�� �� C�� ��� ���Ѵ�.
�̶� �̵��� �� �ִ� ĭ���� ��� ���� B�� �־�� �Ѵ�. ���⼭ ������ B�� C�� ���� ���̴�.
������ ũ��� �� ĭ�� �ִ� ����, �ֻ����� �̵� Ƚ�� K�� �־�������, �� �̵����� ȹ���ϴ� ������ ���� ���غ���.

�� ������ ���� 1���� 7�� ���� �������� �̵��ϴ� Ƚ���� ������Ű�� ������� �����Ǿ� �ִ�.
���� 8�� ���� �������� �̵��ϴ� Ƚ���� �ſ� ũ�� �������.

�Է�
ù° �ٿ� ������ ���� ũ�� N, ���� ũ�� M (2 �� N, M �� 20), �׸��� �̵��ϴ� Ƚ�� K (1 �� K �� 1,000)�� �־�����.
��° �ٺ��� N���� �ٿ� ������ ���� �ִ� ���� ���ʺ��� ��������, �� ���� ���ʺ��� ���� ������� �־�����.
������ �� ĭ�� ���� �ִ� ���� 10 �̸��� �ڿ����̴�.

���
ù° �ٿ� �� �̵����� ȹ���ϴ� ������ ���� ����Ѵ�.

(1,1) ~ (N, M), ù ��ġ (1,1), ù �̵����� ����
N, M, K, dice[3], map[21][21], diceMap[5][4], visited[21][21];
int dx[4], dy[4] -> ��, ��, ��, ��

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
		8) score = find_cnt(); -> visited ���鼭 '1'�� ���� ��ȯ & reset
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



*change_dir(int dir, int s) -> s = 0, �ݴ� chagne, s=1 �̸� �ð� 90��, s=2�̸� �ݽð� 90��
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
	cout << "�ֻ��� ����" << endl;
	cout << '(' << dice[0] << ", " << dice[1] << ")�� ��ġ, ����: " << dice[2] << endl;
	cout << "Score: " << Answer << endl;
	cout << "�ֻ��� ��" << endl;
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
		//cout << time << "�� ��" << endl;
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