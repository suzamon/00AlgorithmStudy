/*
1'13''04'''
������ ���� ���̾�� ����̵��� ������ ���̾���� ������ �� �ִ�.
������ ���̾���� ũ�Ⱑ 2N �� 2N�� ���ڷ� �������� �����ǿ��� �����Ϸ��� �Ѵ�.
��ġ (r, c)�� ������ r�� c���� �ǹ��ϰ�, A[r][c]�� (r, c)�� �ִ� ������ ���� �ǹ��Ѵ�. A[r][c]�� 0�� ��� ������ ���� ���̴�.

���̾���� �����Ϸ��� ������ ������ �ܰ� L�� �����ؾ� �Ѵ�. ���̾���� ���� ���ڸ� 2L �� 2L ũ���� �κ� ���ڷ� ������.
�� ��, ��� �κ� ���ڸ� �ð� �������� 90�� ȸ����Ų��.
���� ������ �ִ� ĭ 3�� �Ǵ� �� �̻�� ���������� ���� ĭ�� ������ ���� 1 �پ���.
(r, c)�� ������ ĭ�� (r-1, c), (r+1, c), (r, c-1), (r, c+1)�̴�. �Ʒ� �׸��� ĭ�� ���� ������ ĭ�� �����ϱ� ���� ���� �����̴�.

������ ���� ���̾���� �� Q�� �����Ϸ��� �Ѵ�. ��� ���̾���� ������ ��, ���� 2������ ���غ���.

1. �����ִ� ���� A[r][c]�� ��
2. �����ִ� ���� �� ���� ū ����� �����ϴ� ĭ�� ����
������ �ִ� ĭ�� ������ �ִ� ĭ�� ������ ������, �� ĭ�� ����Ǿ� �ִٰ� �Ѵ�. ����� ����� ĭ�� �����̴�.

�Է�
ù° �ٿ� N�� Q�� �־�����. ��° �ٺ��� 2N���� �ٿ��� ������ �� ĭ�� �ִ� ������ ���� �־�����.
r��° �ٿ��� c��° �־����� ������ A[r][c] �̴�.
������ �ٿ��� ������ �� ������ �ܰ� L1, L2, ..., LQ�� ������� �־�����.

���
ù° �ٿ� �����ִ� ���� A[r][c]�� ���� ����ϰ�, ��° �ٿ� ���� ū ����� �����ϴ� ĭ�� ������ ����Ѵ�.
��, ����� ������ 0�� ����Ѵ�.

����
2 �� N �� 6
1 �� Q �� 1,000
0 �� A[r][c] �� 100
0 �� Li �� N


N, Q, map[13][13], command[6]

1. Input()
	N, Q, map[2*N][2*N]�� �Է�
2. Solution()
	1. Rotate(sX, sY, size)
		1) int copyMap[13][13], oX, oY, cX, cY;
		2) deque <int> dq;
		3) cY = size;
		3) for(oR = sX; oR < sX + size; oR++) {
		4) for(oC = sY; oC = sY + size; oC++) dq. push_back()
		5) for(cX=1; cX<=size; cX++) copyMap[cX][cY] = dq.front() & dq.pop_front()
		6) cY--; }
		3) for(oR = sX; oR < sX + size; oR++) {
		4) for(oC = sY; oC < sY + size; oC++) {
		5) map[oR][oC] = copyMap[oR - sX + 1][oC - sY + 1];
	2. find_near_ice()
		1) deque <pair<int ,int>> dq;
		2) for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) for(int d=1; d<4; d++) ã�� �� dq�� �ֱ�
		3) while(!dq.empty()) map[x][y] --;











3 1
1 2 3 4 5 6 7 8
9 10 11 12 13 14 15 16
17 18 19 20 21 22 23 24
25 26 27 28 29 30 31 32
33 34 35 36 37 38 39 40
41 42 43 44 45 46 47 48
49 50 51 52 53 54 55 56
57 58 59 60 61 62 63 64
1


*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>
#include <cmath>

using namespace std;

int n, N, Q, Answer = 0;
int map[65][65] = { 0, }, command[1001];

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void print_map() {
	cout << "Map ����" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void find_answer() {
	Answer = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			Answer = Answer + map[i][j];
		}
	}
	cout << Answer << endl;

	int maxSize = 0, tmpSize = 0, sX, sY, nX, nY;
	int visited[65][65] = { 0, };
	queue <pair <int, int>> q;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j] == 0) {
				if(visited[i][j] == 0) visited[i][j] = 1;
				continue;
			}
			if (visited[i][j] == 1) continue;

			tmpSize = 1;
			q.push(make_pair(i, j));
			visited[i][j] = 1;
			while (!q.empty()) {
				sX = q.front().first, sY = q.front().second;
				q.pop();
				for (int d = 0; d < 4; d++) {
					nX = sX + dx[d];
					nY = sY + dy[d];
					if (nX<1 || nX >N || nY<1 || nY>N) continue;

					if (map[nX][nY] >= 1 && visited[nX][nY] == 0) {
						q.push(make_pair(nX, nY));
						visited[nX][nY] = 1;
						tmpSize++;
					}
				}
			}
			if (tmpSize > maxSize) maxSize = tmpSize;

		}
	}


	cout << maxSize << endl;

}

void find_near_ice() {
	int nX, nY, cnt;
	deque <pair <int, int>> dq;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if ((i == 1 && j == 1) || (i == 1 && j == N) || (i == N && j == 1) || (i == N && j == N) ){
				if(map[i][j] > 0) dq.push_back(make_pair(i, j));
				continue;
			}
			else if (map[i][j] == 0) continue;

			cnt = 0;
			for (int d = 0; d < 4; d++) {
				nX = i + dx[d], nY = j + dy[d];
				if (nX<1 || nX >N || nY<1 || nY>N) continue;
				else if (map[nX][nY] >= 1) cnt++;
			}
			if (cnt < 3)dq.push_back(make_pair(i, j));
		}
	}

	while (!dq.empty()) {
		nX = dq.front().first, nY = dq.front().second;
		dq.pop_front();
		map[nX][nY]--;
	}
}

void rot_map(int sX, int sY, int size) {
	int copyMap[65][65];
	int oX, oY, cX, cY;

	deque <int> dq;
	cY = size;
	for (oX = sX; oX < sX + size; oX++) {
		/*
		for (oY = sY; oY < sY + size; oY++)dq.push_back(map[oX][oY]);

		for (cX = 1; cX <= size; cX++) {
			copyMap[cX][cY] = dq.front();
			dq.pop_front();
		}
		cY--;
		*/
		cX = 1;
		for (oY = sY; oY < sY + size; oY++) {
			copyMap[cX][cY] = map[oX][oY];
			cX++;
		}
		cY--;
	}

	for (oX = sX; oX < sX + size; oX++) {
		for (oY = sY; oY < sY + size; oY++) {
			map[oX][oY] = copyMap[oX - sX + 1][oY - sY + 1];
		}
	}
}

void Solution() {
	int time, comSize;
	for (time = 0; time < Q; time++) {
		comSize = command[time];
		for (int x = 1; x < N; x += comSize) {
			for (int y = 1; y < N; y += comSize) {
				rot_map(x, y, comSize);
			}
		}
		find_near_ice();
		//print_map();
	}
	find_answer();
}

void Input() {
	cin >> n >> Q;
	N = pow(2, n);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < Q; i++) {
		cin >> command[i];
		command[i] = pow(2, command[i]);
	}
	
}

int main(void) {
	Input();
	//print_map();
	Solution();
	return 0;
}