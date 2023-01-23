/*
연구소는 크기가 N×M인 직사각형으로 나타낼 수 있으며, 직사각형은 1×1 크기의 정사각형으로 나누어져 있다.
연구소는 빈 칸, 벽으로 이루어져 있으며, 벽은 칸 하나를 가득 차지
일부 칸은 바이러스가 존재하며, 이 바이러스는 상하좌우로 인접한 빈 칸으로 모두 퍼져나갈 수 있다.
새로 세울 수 있는 벽의 개수는 3개이며, 꼭 3개를 세워야 한다.

이때, 0은 빈 칸, 1은 벽, 2는 바이러스가 있는 곳이다. 아무런 벽을 세우지 않는다면,
바이러스는 모든 빈 칸으로 퍼져나갈 수 있다.

벽을 3개 세운 뒤, 바이러스가 퍼질 수 없는 곳을 안전 영역이라고 한다. 위의 지도에서 안전 영역의 크기는 27이다.
연구소의 지도가 주어졌을 때 얻을 수 있는 안전 영역 크기의 최댓값을 구하는 프로그램

첫째 줄에 지도의 세로 크기 N과 가로 크기 M이 주어진다. (3 ≤ N, M ≤ 8)
둘째 줄부터 N개의 줄에 지도의 모양이 주어진다. 0은 빈 칸, 1은 벽, 2는 바이러스가 있는 위치이다.
2의 개수는 2보다 크거나 같고, 10보다 작거나 같은 자연수이다.
빈 칸의 개수는 3개 이상이다.

첫째 줄에 얻을 수 있는 안전 영역의 최대 크기를 출력한다.

1. Input()
	N, M, map, deque virus, virusCnt, deque empty, emptyCnt

2. Solution()
	1. empty에서 3개 선택 -> DFS
	2. DFS 후 copy_map
	3. Simulation -> virus에서 상하좌우 BFS로 구현

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
int map[9][9], copyMap[9][9], wall[3][2];

deque <pair<int, int>> v;
deque <pair <int, int>> e;

int virusCnt, emptyCnt, copyEmptyCnt;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void print_map() {
	
	cout << "Map" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << copyMap[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void Simulaiton() {
	int curX, curY, nextX, nextY;
	queue <pair <int, int>> q;

	for (int i = 0; i < virusCnt; i++) {
		q.push(make_pair(v[i].first, v[i].second));
	}

	while (!q.empty()) {
		curX = q.front().first;
		curY = q.front().second;
		q.pop();

		for (int d = 0; d < 4; d++) {
			nextX = curX + dx[d];
			nextY = curY + dy[d];

			if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) continue;

			if (copyMap[nextX][nextY] == 0) {
				q.push(make_pair(nextX, nextY));
				copyEmptyCnt--;
				copyMap[nextX][nextY] = 2;
			}
		}
	}

	if (Answer < copyEmptyCnt) {
		//print_map();
		Answer = copyEmptyCnt;
	}
}

void copy_map() {
	copyEmptyCnt = emptyCnt;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			copyMap[i][j] = map[i][j];
		}
	}

	for (int i = 0; i < 3; i++) {
		copyMap[wall[i][0]][wall[i][1]] = 1;

	}
}

void DFS(int start, int cnt) {
	if (cnt == 3) {
		copy_map();
		copyEmptyCnt -= 3;

		Simulaiton();
		return;
	}

	for (int i = start; i < emptyCnt; i++) {
		wall[cnt][0] = e[i].first;
		wall[cnt][1] = e[i].second;
		DFS(i + 1, cnt + 1);
	}
}

void Solution() {
	for (int i = 0; i < emptyCnt - 2; i++) {
		wall[0][0] = e[i].first;
		wall[0][1] = e[i].second;
		DFS(i + 1, 1);
	}
}

void Input() {
	virusCnt = 0;
	emptyCnt = 0;

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0) {
				e.push_back(make_pair(i, j));
				emptyCnt++;
			}
			else if (map[i][j] == 2) {
				v.push_back(make_pair(i, j));
				virusCnt++;
			}
		}
	}
}

int main(void) {
	Input();
	Solution();

	cout << Answer << endl;

	return 0;
}