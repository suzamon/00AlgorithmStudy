/*
N×N 크기의 공간에 물고기 M마리와 아기 상어 1마리가 있다. 공간은 1×1 크기의 정사각형 칸으로 나누어져 있다.
한 칸에는 물고기가 최대 1마리 존재한다.

아기 상어와 물고기는 모두 크기를 가지고 있고, 이 크기는 자연수이다.
가장 처음에 아기 상어의 크기는 2이고, 아기 상어는 1초에 상하좌우로 인접한 한 칸씩 이동한다.

아기 상어는 자신의 크기보다 큰 물고기가 있는 칸은 지나갈 수 없고, 나머지 칸은 모두 지나갈 수 있다.
아기 상어는 자신의 크기보다 작은 물고기만 먹을 수 있다. 따라서, 크기가 같은 물고기는 먹을 수 없지만,
그 물고기가 있는 칸은 지나갈 수 있다.

아기 상어가 어디로 이동할지 결정하는 방법은 아래와 같다.

더 이상 먹을 수 있는 물고기가 공간에 없다면 아기 상어는 엄마 상어에게 도움을 요청한다.
먹을 수 있는 물고기가 1마리라면, 그 물고기를 먹으러 간다.
먹을 수 있는 물고기가 1마리보다 많다면, 거리가 가장 가까운 물고기를 먹으러 간다.
거리는 아기 상어가 있는 칸에서 물고기가 있는 칸으로 이동할 때, 지나야하는 칸의 개수의 최솟값이다.
거리가 가까운 물고기가 많다면, 가장 위에 있는 물고기, 그러한 물고기가 여러마리라면, 가장 왼쪽에 있는 물고기를 먹는다.
아기 상어의 이동은 1초 걸리고, 물고기를 먹는데 걸리는 시간은 없다고 가정한다.
즉, 아기 상어가 먹을 수 있는 물고기가 있는 칸으로 이동했다면, 이동과 동시에 물고기를 먹는다.
물고기를 먹으면, 그 칸은 빈 칸이 된다.

아기 상어는 자신의 크기와 같은 수의 물고기를 먹을 때 마다 크기가 1 증가한다.
예를 들어, 크기가 2인 아기 상어는 물고기를 2마리 먹으면 크기가 3이 된다.

공간의 상태가 주어졌을 때, 아기 상어가 몇 초 동안 엄마 상어에게 도움을 요청하지 않고 물고기를 잡아먹을 수 있는지
구하는 프로그램을 작성하시오.

입력
첫째 줄에 공간의 크기 N(2 ≤ N ≤ 20)이 주어진다.

둘째 줄부터 N개의 줄에 공간의 상태가 주어진다. 공간의 상태는 0, 1, 2, 3, 4, 5, 6, 9로 이루어져 있고,
아래와 같은 의미를 가진다.

0: 빈 칸
1, 2, 3, 4, 5, 6: 칸에 있는 물고기의 크기
9: 아기 상어의 위치
아기 상어는 공간에 한 마리 있다.

출력
첫째 줄에 아기 상어가 엄마 상어에게 도움을 요청하지 않고 물고기를 잡아먹을 수 있는 시간을 출력한다.

N, map[21][21]
shark[4] = x, y, size, 먹은 물고기
deque <pair <int, pair <int, int>>> nextPos;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

1. Input()
	N, map[N][N], shark[3]

2. Solution()
	1) while(1) & time = 0
	2) int find_next() ; BFS로 탐색, 1이면 상어 이동 & time++, 0이면 종료 후 time 출력
		2-1) queue <pair <int, pair<int, int>>> p에 time, 상어 시작 위치 저장 & sharkSize에 shark[2] 저장
		2-2) while(!q.empty())에 넣어 탐색
		2-2-1) 탐색할 때, nextPos의 size가 1보다 크면 현재 time 값과 비교해서 크면 return;
		2-3) 상좌하우 탐색 (상어보다 큰 물고기나 map을 벗어나면 다음)
		2-4) 상좌하우 탐색했을 때, 자기보다 작은 물고기 만나면 nextPos에 넣기
		2-5) 2-4)에서 만약 nextPos의 size가 1보다 크면 time값과 x, y값 비교
		2-6) 조건 값 만족하면 nextPos 갱신, 아니면 2-2-1)부터 반복
		2-7) nextPos size 반환
	3) int move_shark(int time)
		3-1) nextPos 값에 맞게끔 상어 이동 및 소요 시간 더하기
		3-2) 소요 시간 반환
	4) 2) 반환 값이 '0'이면 time 값 출력
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int N, Answer = 0;
int map[21][21] = { 0, };
int shark[4] = { 0, };

deque < pair <int, pair<int, int>>> nextPos;

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };

int move_shark() {
	int nT, nX, nY;
	nT = nextPos.front().first;
	nX = nextPos.front().second.first;
	nY = nextPos.front().second.second;
	map[nX][nY] = 0;
	nextPos.pop_front();

	shark[0] = nX;
	shark[1] = nY;
	shark[3]++;
	if (shark[2] == shark[3]) {
		shark[2]++;
		shark[3] = 0;
	}

	return nT;
}

int find_next() {
	int visited[21][21] = { 0, };
	int sharkSize = shark[2];
	queue < pair <int, pair<int, int>>> q;
	q.push(make_pair(0, make_pair(shark[0], shark[1])));
	visited[shark[0]][shark[1]] = 1;

	int sT, sX, sY, nT, nX, nY;

	while (!q.empty()) {
		sT = q.front().first;
		sX = q.front().second.first;
		sY = q.front().second.second;
		q.pop();
		
		for (int d = 0; d < 4; d++) {
			nX = sX + dx[d];
			nY = sY + dy[d];
			nT = sT + 1;
			if (nX < 0 || nX >= N || nY < 0 || nY >= N) continue;
			if (visited[nX][nY] == 1) continue;
			if (nextPos.size() == 1 && nextPos.front().first < nT) continue;

			if (map[nX][nY] < sharkSize && map[nX][nY] > 0) {
				if (nextPos.size() == 0) {
					nextPos.push_back(make_pair(nT, make_pair(nX, nY)));
					visited[nX][nY] = 1;
				}
				else if (nextPos.front().first > nT) {
					nextPos.pop_front();
					nextPos.push_back(make_pair(nT, make_pair(nX, nY)));
					visited[nX][nY] = 1;
				}
				else if (nextPos.front().first == nT && nextPos.front().second.first > nX) {
					nextPos.pop_front();
					nextPos.push_back(make_pair(nT, make_pair(nX, nY)));
					visited[nX][nY] = 1;
				}
				else if (nextPos.front().first == nT && nextPos.front().second.first == nX && nextPos.front().second.second > nY) {
					nextPos.pop_front();
					nextPos.push_back(make_pair(nT, make_pair(nX, nY)));
					visited[nX][nY] = 1;
				}
			}
			else if (map[nX][nY] == sharkSize || map[nX][nY] == 0) {
				q.push(make_pair(nT, make_pair(nX, nY)));
				visited[nX][nY] = 1;
			}

		}
	}

	return nextPos.size();
}

void Solution() {
	int flag = 0, time = 0;
	while (1) {
		flag = find_next();
		if (flag == 0) break;

		time = time + move_shark();
	}

	cout << time << endl;
}

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				shark[0] = i;
				shark[1] = j;
				shark[2] = 2;
				map[i][j] = 0;
			}
		}
	}
}


int main(void) {
	Input();
	Solution();
	return 0;
}