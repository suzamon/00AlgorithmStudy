/*
홍익이는 사악한 마법사의 꾐에 속아 N x M 미로 (Hx, Hy) 위치에서 시작
마법사가 만든 미로의 탈출 위치(Ex, Ey)를 알고 있다.
하지만 미로에는 곳곳에 마법사가 설치한 벽이 있어 홍익이가 탈출하기 어려움
홍익이는 마법사의 연구실에서 훔친 지팡이가 있어, 벽을 길로 만들 수 있다. 마법의 지팡이는 단 한 번만 사용 가능
이때, 홍익이를 도와 미로에서 탈출할 수 있는지 알아보고, 할 수 있다면 가장 빠른 경로의 거리 D는 얼마인지 알아보자.

N M
Hx Hy
Ex Ey
N X M 행렬

2 ≤ N ≤ 1000, 2 ≤ M ≤ 1000
1 ≤ Hx, Hy, Ex, Ey ≤ 1000
(Hx, Hy)≠ (Ex, Ey)
행렬은 0과 1로만 이루어져 있고, 0이 빈 칸, 1이 벽이다.

-> BFS로 구현


1. Input() : startPos[2], endPos[2], map[1001][1001]

2. Solution()
	1. find_exit(int startX, startY)
		-> BFS로 구현 -> queue <int, int, int, int> x, y, 거리, 마법사용 여부
		-> 네 방향 검색 후 길이면 이동해서 queue 추가 아니면, 마법 사용 X면 마법 사용 -> flag
		-> 마법 사용한 경우에는 visited변수 '2'로 셋
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
int startPos[2] = { 0, };
int exitPos[2] = { 0, };
int map[1002][1002] = { 0, };
int visited[1002][1002] = { 0, };

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void find_exit(int startX, int startY) {
	queue < pair<pair<int, int>, pair<int, int>>> q;
	q.push(make_pair(make_pair(startX, startY), make_pair(0, 0)));
	
	int length, magicFlag, nextX, nextY;
	while (!q.empty()) {
		startX = q.front().first.first;
		startY = q.front().first.second;
		length = q.front().second.first;
		magicFlag = q.front().second.second;
		q.pop();
		if (startX == exitPos[0] && startY == exitPos[1]) {
			Answer = length;
			break;
		}

		for (int i = 0; i < 4; i++) {
			nextX = startX + dx[i];
			nextY = startY + dy[i];
			if (nextX <= 0 || nextX > N || nextY <= 0 || nextY > M) continue;

			if (map[nextX][nextY] == 1 && magicFlag == 0 && visited[nextX][nextY] == 0) {
				visited[nextX][nextY] == 2;
				q.push(make_pair(make_pair(nextX, nextY), make_pair(length + 1, 1)));
			}
			else if (map[nextX][nextY] == 0 && visited[nextX][nextY] == 0) {
				visited[nextX][nextY] = magicFlag + 1;
				q.push(make_pair(make_pair(nextX, nextY), make_pair(length + 1, magicFlag)));
			}
			else if (map[nextX][nextY] == 0 && visited[nextX][nextY] == 2 && magicFlag ==0) {
				visited[nextX][nextY] = magicFlag + 1;
				q.push(make_pair(make_pair(nextX, nextY), make_pair(length + 1, magicFlag)));
			}
		}
	}
}

void Solution() {

	find_exit(startPos[0], startPos[1]);
}

void Input() {
	cin >> N >> M;
	cin >> startPos[0] >> startPos[1];
	cin >> exitPos[0] >> exitPos[1];

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j];
		}
	}
}

int main(void) {
	Input();
	Solution();
	if (Answer == 0) Answer = -1;
	cout << Answer << endl;

	return 0;
}