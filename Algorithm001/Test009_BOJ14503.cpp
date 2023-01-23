/*
�κ� û�ұⰡ �־����� ��, û���ϴ� ������ ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

�κ� û�ұⰡ �ִ� ��Ҵ� N��M ũ���� ���簢������ ��Ÿ�� �� ������,
1��1ũ���� ���簢�� ĭ���� �������� �ִ�. ������ ĭ�� �� �Ǵ� �� ĭ�̴�.
û�ұ�� �ٶ󺸴� ������ ������, �� ������ ��, ��, ��, ���� �ϳ��̴�.
������ �� ĭ�� (r, c)�� ��Ÿ�� �� �ְ�, r�� �������κ��� ������ ĭ�� ����, c�� �������� ���� ������ ĭ�� �����̴�.

1. ���� ��ġ�� û���Ѵ�.
2. ���� ��ġ���� ���� ������ �������� ���� ������� ���ʴ�� ������ ĭ�� Ž���Ѵ�.
	���� ���⿡ ���� û������ ���� ������ �����Ѵٸ�, �� �������� ȸ���� ���� �� ĭ�� �����ϰ� 1������ �����Ѵ�.
	���� ���⿡ û���� ������ ���ٸ�, �� �������� ȸ���ϰ� 2������ ���ư���.
	�� ���� ��� û�Ұ� �̹� �Ǿ��ְų� ���� ��쿡��, �ٶ󺸴� ������ ������ ä�� �� ĭ ������ �ϰ� 2������ ���ư���.
	�� ���� ��� û�Ұ� �̹� �Ǿ��ְų� ���̸鼭, ���� ������ ���̶� ������ �� �� ���� ��쿡�� �۵��� �����.
	�κ� û�ұ�� �̹� û�ҵǾ��ִ� ĭ�� �� û������ ������, ���� ����� �� ����.


ù° �ٿ� ���� ũ�� N�� ���� ũ�� M�� �־�����. (3 �� N, M �� 50)
��° �ٿ� �κ� û�ұⰡ �ִ� ĭ�� ��ǥ (r, c)�� �ٶ󺸴� ���� d�� �־�����.
d�� 0�� ��쿡�� ������, 1�� ��쿡�� ������, 2�� ��쿡�� ������, 3�� ��쿡�� ������ �ٶ󺸰� �ִ� ���̴�.
��° �ٺ��� N���� �ٿ� ����� ���°� ���ʺ��� ���� �������, �� ���� ���ʺ��� ���� ������� �־�����.
�� ĭ�� 0, ���� 1�� �־�����. ������ ù ��, ������ ��, ù ��, ������ ���� �ִ� ��� ĭ�� ���̴�.
�κ� û�ұⰡ �ִ� ĭ�� ���´� �׻� �� ĭ�̴�.

�κ� û�ұⰡ û���ϴ� ĭ�� ������ ����Ѵ�.

dx, dy -> ��, ��, ��, ��

1. Input()
	N, M, map[N][M], robot[3]

2. Simualtion()
	1. ���� ��ġ û��(robotCnt++)
	2. ���� ȸ�� �� Ž�� -> 4�� �ݺ�
	3. 4�� �ݺ��ص� ������ �ڷ� ��ĭ �̵� -> ���̸� ����
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
		//cout << robot[0] << ", " << robot[1] << "û�� �Ϸ�" << endl;
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