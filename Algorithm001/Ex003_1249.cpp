/*
연합군과 독일군 전투로 도로 파손된 상태 -> 도로 복구 (출발지 S에서 도착지 G까지)
도로 파여진 깊이에 비례해서 복구시간 증가 -> 가는 경로 중 가장 짧은 경로에 대한 총 복구 시간
깊이 1-> 복구에 드는 시간 : 1
(0,0) 출발지 -> (N-1, N-1) 도착지, 이동 시간 고려 X
map[x][y] -> 파여진 도로의 깊이

NxN (N<=100)
map[x][y]

1. Input() : N과 map[N][N], start[2] = (0,0), end[2] = (N-1,N-1), dx[2], dy[2] : →, ↓
2. Solution() :
	1) BFS() : q(startX, startY, time, sum) (startX == endX, startY == endY면 비교)
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdio>
#include <string>

using namespace std;

int N, Answer;
int map[101][101];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

int startPos[2];
int endPos[2];

void BFS() {
	queue < pair<pair<int, int>, pair<int, int>>> q;
	int startX = 0, startY = 0, sum = 0, time =0, nextX, nextY;
	int visited[101][101] = { 0, };

	q.push(make_pair(make_pair(startX, startY), make_pair(time, sum)));
	visited[0][0] == -1;
	while (!q.empty()) {
		startX = q.front().first.first;
		startY = q.front().first.second;
		time = q.front().second.first;
		sum = q.front().second.second;
		q.pop();

		if (startX == endPos[0] && startY == endPos[1]) {
			if (Answer == -1) Answer = sum;
			else if (Answer > sum) Answer = sum;
			continue;
		}

		for (int i = 0; i < 4; i++) {
			nextX = startX + dx[i];
			nextY = startY + dy[i];
			if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N) continue;
			if (visited[nextX][nextY] == 0) {
				q.push(make_pair(make_pair(nextX, nextY), make_pair(time + 1, sum + map[nextX][nextY])));
				if (sum + map[nextX][nextY] == 0) visited[nextX][nextY] = -1;
				else visited[nextX][nextY] = sum + map[nextX][nextY];
			}
			else if (visited[nextX][nextY] > sum + map[nextX][nextY]) {
				q.push(make_pair(make_pair(nextX, nextY), make_pair(time + 1, sum + map[nextX][nextY])));
				if (sum + map[nextX][nextY] == 0) visited[nextX][nextY] = -1;
				else visited[nextX][nextY] = sum + map[nextX][nextY];
			}
			
			
		}
	}
}

void Solution() {
	BFS();
}

void Input() {
	string temp;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> temp;
		for (int j = 0; j < N; j++) {
			map[i][j] = temp.at(j) - '0';
		}
	}

	startPos[0] = 0;
	startPos[1] = 0;

	endPos[0] = N - 1;
	endPos[1] = N - 1;

	Answer = -1;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		Input();
		Solution();
		cout << '#' << test_case << ' ' << Answer << endl;
	}
	return 0;
}