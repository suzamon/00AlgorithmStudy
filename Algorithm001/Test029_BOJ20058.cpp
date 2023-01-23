/*
1'13''04'''
마법사 상어는 파이어볼과 토네이도를 조합해 파이어스톰을 시전할 수 있다.
오늘은 파이어스톰을 크기가 2N × 2N인 격자로 나누어진 얼음판에서 연습하려고 한다.
위치 (r, c)는 격자의 r행 c열을 의미하고, A[r][c]는 (r, c)에 있는 얼음의 양을 의미한다. A[r][c]가 0인 경우 얼음이 없는 것이다.

파이어스톰을 시전하려면 시전할 때마다 단계 L을 결정해야 한다. 파이어스톰은 먼저 격자를 2L × 2L 크기의 부분 격자로 나눈다.
그 후, 모든 부분 격자를 시계 방향으로 90도 회전시킨다.
이후 얼음이 있는 칸 3개 또는 그 이상과 인접해있지 않은 칸은 얼음의 양이 1 줄어든다.
(r, c)와 인접한 칸은 (r-1, c), (r+1, c), (r, c-1), (r, c+1)이다. 아래 그림의 칸에 적힌 정수는 칸을 구분하기 위해 적은 정수이다.

마법사 상어는 파이어스톰을 총 Q번 시전하려고 한다. 모든 파이어스톰을 시전한 후, 다음 2가지를 구해보자.

1. 남아있는 얼음 A[r][c]의 합
2. 남아있는 얼음 중 가장 큰 덩어리가 차지하는 칸의 개수
얼음이 있는 칸이 얼음이 있는 칸과 인접해 있으면, 두 칸을 연결되어 있다고 한다. 덩어리는 연결된 칸의 집합이다.

입력
첫째 줄에 N과 Q가 주어진다. 둘째 줄부터 2N개의 줄에는 격자의 각 칸에 있는 얼음의 양이 주어진다.
r번째 줄에서 c번째 주어지는 정수는 A[r][c] 이다.
마지막 줄에는 마법사 상어가 시전한 단계 L1, L2, ..., LQ가 순서대로 주어진다.

출력
첫째 줄에 남아있는 얼음 A[r][c]의 합을 출력하고, 둘째 줄에 가장 큰 덩어리가 차지하는 칸의 개수를 출력한다.
단, 덩어리가 없으면 0을 출력한다.

제한
2 ≤ N ≤ 6
1 ≤ Q ≤ 1,000
0 ≤ A[r][c] ≤ 100
0 ≤ Li ≤ N


N, Q, map[13][13], command[6]

1. Input()
	N, Q, map[2*N][2*N]에 입력
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
		2) for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) for(int d=1; d<4; d++) 찾은 후 dq에 넣기
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
	cout << "Map 정보" << endl;
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