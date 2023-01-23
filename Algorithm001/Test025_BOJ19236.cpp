/*
아기 상어가 성장해 청소년 상어가 되었다.

4×4크기의 공간이 있고, 크기가 1×1인 정사각형 칸으로 나누어져 있다. 공간의 각 칸은 (x, y)와 같이 표현하며,
x는 행의 번호, y는 열의 번호이다. 한 칸에는 물고기가 한 마리 존재한다. 각 물고기는 번호와 방향을 가지고 있다.
번호는 1보다 크거나 같고, 16보다 작거나 같은 자연수이며, 두 물고기가 같은 번호를 갖는 경우는 없다.
방향은 8가지 방향(상하좌우, 대각선) 중 하나이다.

오늘은 청소년 상어가 이 공간에 들어가 물고기를 먹으려고 한다. 청소년 상어는 (0, 0)에 있는 물고기를 먹고,
(0, 0)에 들어가게 된다. 상어의 방향은 (0, 0)에 있던 물고기의 방향과 같다. 이후 물고기가 이동한다.

물고기는 번호가 작은 물고기부터 순서대로 이동한다. 물고기는 한 칸을 이동할 수 있고,
이동할 수 있는 칸은 빈 칸과 다른 물고기가 있는 칸, 이동할 수 없는 칸은 상어가 있거나, 공간의 경계를 넘는 칸이다.
각 물고기는 방향이 이동할 수 있는 칸을 향할 때까지 방향을 45도 반시계 회전시킨다.
만약, 이동할 수 있는 칸이 없으면 이동을 하지 않는다. 그 외의 경우에는 그 칸으로 이동을 한다.
물고기가 다른 물고기가 있는 칸으로 이동할 때는 서로의 위치를 바꾸는 방식으로 이동한다.

물고기의 이동이 모두 끝나면 상어가 이동한다. 상어는 방향에 있는 칸으로 이동할 수 있는데,
한 번에 여러 개의 칸을 이동할 수 있다. 상어가 물고기가 있는 칸으로 이동했다면, 그 칸에 있는 물고기를 먹고,
그 물고기의 방향을 가지게 된다. 이동하는 중에 지나가는 칸에 있는 물고기는 먹지 않는다.
물고기가 없는 칸으로는 이동할 수 없다. 상어가 이동할 수 있는 칸이 없으면 공간에서 벗어나 집으로 간다.
상어가 이동한 후에는 다시 물고기가 이동하며, 이후 이 과정이 계속해서 반복된다.

상어가 먹을 수 있는 물고기 번호의 합의 최댓값을 구해보자.


입력
첫째 줄부터 4개의 줄에 각 칸의 들어있는 물고기의 정보가 1번 행부터 순서대로 주어진다.
물고기의 정보는 두 정수 ai, bi로 이루어져 있고, ai는 물고기의 번호, bi는 방향을 의미한다.
방향 bi는 8보다 작거나 같은 자연수를 의미하고, 1부터 순서대로 ↑, ↖, ←, ↙, ↓, ↘, →, ↗ 를 의미한다.

출력
상어가 먹을 수 있는 물고기 번호의 합의 최댓값을 출력한다.

Answer =0, shark[3], map[4][4], fish[17][4], -> 상태, x, y, dir

1. Input()
	fish[4]에 정보 업데이트(초기 상태: 0, 죽으면: 1), map에 물고기 번호 업데이트
2. Solution()
	1) shark -> 0,0에 있는 물고기 슥샥 & map[0][0]에 -1로 표기 & Answer = Answer + map[0][0]
	2) move_fish() -> 1번 부터 16번 까지 물고기 이동 시뮬레이션
		1) for(int idx=1; idx<17; idx++)
		2) fish[idx][0] == 1, continue;
		3) 죽은 상태 아니면 이동 -> nX = x + dx[dir] & nY = y + dy[dir]
		4) 맵 벗어나거나 상어 있으면 dir 변경 => dir = change_dir(dir) -> 8번 반복하면 X
		5) if(map[nX][nY] == 0)이면 바로 fish에 업데이트 & map 업데이트
		6) else if(map[nX][nY] != 0)이면, 해당 위치에 있는 물고기랑 위치 변경 & map 업데이트
	3) move_shark(int sum)
		1) 가능한 position 저장 -> posArr[4][2]에 저장
		2) 각 posArr만큼 DFS 시작
		3) 만약 갈 수 있는 곳 없으면 return
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int N, Answer = 0;
int shark[3] = { 0, }, map[4][4] = { 0, }, fish[17][4] = { 0, };
int dx[9] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[9] = { 0, 0, -1, -1,-1, 0, 1 ,1, 1 };

void print_map() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

int change_dir(int dir) {
	int nDir = dir + 1;
	if (nDir == 9) nDir = 1;
	return nDir;
}

void move_fish() {
	int idx, x, y, dir, nX, nY, nDir, idx2, cnt;
	
	for (idx = 1; idx < 17; idx++) {
		if (fish[idx][0] == 1) continue;
		x = fish[idx][1], y = fish[idx][2], dir = fish[idx][3];
		cnt = 0, nDir = dir;
		while (1) {
			if (cnt == 8) break;

			cnt++;
			nX = x + dx[nDir];
			nY = y + dy[nDir];
			if (nX < 0 || nX >= 4 || nY < 0 || nY >= 4 || map[nX][nY] == -1) {
				nDir = change_dir(nDir);
				continue;
			}

			if (map[nX][nY] == 0) {
				map[x][y] = 0;
				map[nX][nY] = idx;
				fish[idx][1] = nX, fish[idx][2] = nY, fish[idx][3] = nDir;
				break;
			}
			else {
				idx2 = map[nX][nY];

				map[x][y] = idx2;
				fish[idx2][1] = x, fish[idx2][2] = y;

				map[nX][nY] = idx;
				fish[idx][1] = nX, fish[idx][2] = nY, fish[idx][3] = nDir;
				break;
			}
		}
	}
}

void move_shark(int sum) {
	int x, y, dir, nX, nY, posCnt = 0;
	int pos[4][2] = { 0, };

	x = shark[0], y = shark[1], dir = shark[2];
	nX = x, nY = y;
	posCnt = 0;

	for (int i = 0; i < 4; i++) {
		nX = nX + dx[dir];
		nY = nY + dy[dir];

		if (nX < 0 || nX >= 4 || nY < 0 || nY >= 4) break;
		else if(map[nX][nY] == 0) continue;
		
		pos[posCnt][0] = nX;
		pos[posCnt][1] = nY;
		posCnt++;
	}

	if (posCnt == 0) {
		if (sum > Answer) Answer = sum;
		return;
	}

	int fishIdx = 0;
	if (posCnt == 1) {
		nX = pos[0][0];
		nY = pos[0][1];

		map[x][y] = 0;

		fishIdx = map[nX][nY];
		fish[fishIdx][0] = 1;

		map[nX][nY] = -1;
		shark[0] = nX;
		shark[1] = nY;
		shark[2] = fish[fishIdx][3];

		move_fish();

		move_shark(sum + fishIdx);
	}
	else {
		int copyMap[4][4], copyFish[17][4];

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				copyMap[i][j] = map[i][j];
			}
		}
		for (int i = 1; i < 17; i++) {
			for (int j = 0; j < 4; j++) {
				copyFish[i][j] = fish[i][j];
			}
		}

		for (int i = 0; i < posCnt; i++) {
			nX = pos[i][0];
			nY = pos[i][1];

			map[x][y] = 0;

			fishIdx = map[nX][nY];
			fish[fishIdx][0] = 1;

			map[nX][nY] = -1;
			shark[0] = nX;
			shark[1] = nY;
			shark[2] = fish[fishIdx][3];

			move_fish();
			move_shark(sum + fishIdx);
			
			
			map[x][y] = -1;
			fish[fishIdx][0] = 0;
			map[nX][nY] = fishIdx;
			shark[0] = x;
			shark[1] = y;
			shark[2] = dir;

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					map[i][j] = copyMap[i][j];
				}
			}
			for (int i = 1; i < 17; i++) {
				for (int j = 0; j < 4; j++) {
					fish[i][j] = copyFish[i][j];
				}
			}
		}

	}
}

void Solution() {
	int idx = map[0][0];
	Answer = Answer + idx;
	shark[0] = 0, shark[1] = 0;
	shark[2] = fish[idx][3];
	fish[idx][0] = 1;
	map[0][0] = -1;

	move_fish();
	move_shark(Answer);
	cout << Answer << endl;
}

void Input() {
	int idx;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> idx;
			fish[idx][0] = 0;
			fish[idx][1] = i;
			fish[idx][2] = j;
			cin >> fish[idx][3];
			map[i][j] = idx;
		}
	}
}

int main(void) {
	Input();
	Solution();

	return 0;
}