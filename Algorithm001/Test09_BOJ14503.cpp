/*\
����
�κ� û�ұⰡ �־����� ��, û���ϴ� ������ ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

�κ� û�ұⰡ �ִ� ��Ҵ� N��M ũ���� ���簢������ ��Ÿ�� �� ������,
1��1ũ���� ���簢�� ĭ���� �������� �ִ�. ������ ĭ�� �� �Ǵ� �� ĭ�̴�.
û�ұ�� �ٶ󺸴� ������ ������, �� ������ ��, ��, ��, ���� �ϳ��̴�.
������ ���ʿ������� r��°, ���ʿ������� c��°�� ��ġ�� ĭ�� (r, c)�� ��Ÿ�� �� �ִ�.

�κ� û�ұ�� ������ ���� �۵��Ѵ�.

1. ���� ��ġ�� û���Ѵ�.
2. ���� ��ġ���� ������ �ݺ��ϸ鼭 ������ ĭ�� Ž���Ѵ�.
	a. ���� ��ġ�� �ٷ� ���ʿ� ���� û������ ���� �� ������ �����Ѵٸ�,
	   ���� �������� ȸ���� ���� �� ĭ�� �����ϰ� 1������ ���ư���.
	   �׷��� ���� ���, ���� �������� ȸ���Ѵ�. �̶�, ������ ���� �ٶ󺸴� ������ �������� �Ѵ�.
	b. 1������ ���ư��ų� �������� �ʰ� 2a�� �ܰ谡 �������� �� �� ����Ǿ��� ���,
		�ٷ� ������ ���̶�� �۵��� �����. �׷��� �ʴٸ� �� ĭ �����Ѵ�.

�Է�
ù° �ٿ� ���� ũ�� N�� ���� ũ�� M�� �־�����. (3 �� N, M �� 50)
��° �ٿ� �κ� û�ұⰡ �ִ� ĭ�� ��ǥ (r, c)�� �ٶ󺸴� ���� d�� �־�����.
d�� 0�� ��쿡�� ������, 1�� ��쿡�� ������, 2�� ��쿡�� ������,
3�� ��쿡�� ������ �ٶ󺸰� �ִ� ���̴�.

��° �ٺ��� N���� �ٿ� ����� ���°� ���ʺ��� ���� �������,
�� ���� ���ʺ��� ���� ������� �־�����.
�� ĭ�� 0, ���� 1�� �־�����. ������ ù ��, ������ ��, ù ��, ������ ���� �ִ� ��� ĭ�� ���̴�.
�κ� û�ұⰡ �ִ� ĭ�� ���´� �׻� �� ĭ�̴�.

���
�κ� û�ұⰡ û���ϴ� ĭ�� ������ ����Ѵ�.

N, M, Answer
int map[51][51] = {0, }, visited[51][51] ={0, };
int dx[4], dy[4] -> 0: ��, 1: ��, 2: ��, 3: ��
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
	cout << "�κ� ��ġ: " << robot[0] << ", " << robot[1] << ", ����: " << robot[2] << endl;
	cout << "��" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << "�湮 ��" << endl;
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