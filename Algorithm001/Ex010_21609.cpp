/*
N×N인 격자에서 진행, 검은색 블록, 무지개 블록, 일반 블록, 일반 블록은 M가지 색상 -> 색은 M이하의 자연수로 표현
검은색 블록은 -1, 무지개 블록은 0으로 표현
 (i, j)는 격자의 i번 행, j번 열을 의미하고, |r1 - r2| + |c1 - c2| = 1을 만족하는 두 칸 (r1, c1)과 (r2, c2)를 인접한 칸

블록 그룹은 연결된 블록의 집합이다.
그룹에는 일반 블록이 적어도 하나 있어야 하며, 일반 블록의 색은 모두 같아야 한다.
검은색 블록은 포함되면 안 되고, 무지개 블록은 얼마나 들어있든 상관없다. 그룹에 속한 블록의 개수는 2보다 크거나 같아야 하며
임의의 한 블록에서 그룹에 속한 인접한 칸으로 이동해서 그룹에 속한 다른 모든 칸으로 이동할 수 있어야한다.
블록 그룹의 기준 블록은 무지개 블록이 아닌 블록 중에서
행의 번호가 가장 작은 블록 && 열의 번호가 가장 작은 블록이다.

1. 크기가 가장 큰 블록 그룹을 찾는다. -> 여러 개라면 포함된 무지개 블록의 수가 가장 많은 블록 그룹
 -> 기준 블록의 행이 가장 큰 것 -> 열이 가장 큰 것을 찾는다.
2. 1에서 찾은 블록 그룹의 모든 블록을 제거한다. 블록 그룹에 포함된 블록의 수를 B라고 했을 때, B^2점을 획득한다.
3. 격자에 중력이 작용한다.(검은색 블록 이동 X)
4. 격자가 90도 반시계 방향으로 회전한다.
5. 다시 격자에 중력이 작용한다.

첫째 줄에 격자 한 변의 크기 N, 색상의 개수 M이 주어진다.

둘째 줄부터 N개의 줄에 격자의 칸에 들어있는 블록의 정보가 1번 행부터 N번 행까지 순서대로 주어진다.
각 행에 대한 정보는 1열부터 N열까지 순서대로 주어진다.
입력으로 주어지는 칸의 정보는 -1, 0, M이하의 자연수로만 이루어져 있다.

1 ≤ N ≤ 20
1 ≤ M ≤ 5

1. Input() : N, M, map[N][M], deque rainBow <int, int>

2. Solve()
	1) find_rainbowBlock() -> 무지개 블록 중 겹쳐져 있는 블록 제거
	2) find_large_block(int startX, int startY) -> BFS로 구현(무지개 블록별)
		: 이동하는 칸 없으면 tmpArr[5]랑 비교 -> color, size, rainbowCnt, oR, oC 순으로!
		: 각 무지개블록별 가장 큰 블록을 deque dq에 저장(color, size, rainbowCnt, oR, oC)
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
int map[21][21];

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

deque <pair <int, int>> r;

deque <pair <int, pair <pair <int, int>, pair <int, int>>>> dq;

void print_map() {
	cout << "Map" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void print() {
	cout << "무지개 블록 그룹" << endl;
	for (int i = 0; i < r.size(); i++) {
		cout << r[i].first << ", " << r[i].second << endl;
	}
	cout << endl;
}

bool compare(pair <int, pair <pair <int, int>, pair <int, int>>> a, pair <int, pair <pair <int, int>, pair <int, int>>> b) {
	if (a.second.first.first == b.second.first.first) {
		if (a.second.first.second == b.second.first.second) {
			if (a.second.second.first == b.second.second.first) {
				return a.second.second.second > b.second.second.second;
			}
			return a.second.second.first > b.second.second.first;
		}
		return a.second.first.second > b.second.first.second;
	}
	return a.second.first.first > b.second.first.first;
}

bool inRange(int r, int c) {
	if (r >= 0 && r < N && c >= 0 && c < N) return true;
	else return false;
}

void rotate_map() {
	int copyMap[21][21];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			copyMap[i][j] = map[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = copyMap[j][N - 1 - i];
		}
	}
}

void remove_map() {
	int startR = -1;
	for (int c = 0; c < N; c++) {
		startR = -1;
		for (int r = N - 1; r >= 0; r--) {
			if (startR == -1 && map[r][c] == M + 1) startR = r;
			else if (map[r][c] == -1) {
				if (r > 0 && map[r - 1][c] == M + 1) startR = r - 1;
				else startR = -1;
			}
			else if (startR != -1 && map[r][c] < M) {
				map[startR][c] = map[r][c];
				map[r][c] = M + 1;
				startR--;
			}
		}
	}
}

void remove_block(int color, int startX, int startY) {
	queue <pair <int, int>> q;
	int visited[21][21] = { 0, };
	int nextX, nextY;
	q.push(make_pair(startX, startY));
	visited[startX][startY] = 1;
	map[startX][startY] = M + 1;

	while(!q.empty()) {
		startX = q.front().first;
		startY = q.front().second;
		q.pop();
		for (int d = 0; d < 4; d++) {
			nextX = startX + dx[d];
			nextY = startY + dy[d];
			if (!inRange(nextX, nextY)) continue;

			if (map[nextX][nextY] == color && visited[nextX][nextY] == 0) {
				visited[nextX][nextY] = 1;
				map[nextX][nextY] = M + 1;
				q.push(make_pair(nextX, nextY));
			}
			else if (map[nextX][nextY] == 0 && visited[nextX][nextY] == 0) {
				visited[nextX][nextY] = 1;
				map[nextX][nextY] = M + 1;
				q.push(make_pair(nextX, nextY));
			}
		}
	}
}

void find_large_block(int startX, int startY) {
	int nextX, nextY;
	int color, size, rainbowCnt, oR, oC;
	int visited[51][51] = { 0, };
	int tmpArr[5] = { 0, };
	queue <pair <int, int>> q1;
	queue <pair <int, int>> q2;

	//1. rainbowBlock 탐색 -> q2에 저장
	visited[startX][startY] = 1;
	q1.push(make_pair(startX, startY));
	q2.push(make_pair(startX, startY));

	while (!q1.empty()) {
		startX = q1.front().first;
		startY = q1.front().second;
		q1.pop();
		for (int d = 0; d < 4; d++) {
			nextX = startX + dx[d];
			nextY = startY + dy[d];
			if (!inRange(nextX, nextY)) continue;
			else if (map[nextX][nextY] == 0 && visited[nextX][nextY] == 0) {
				visited[nextX][nextY] = 1;
				q1.push(make_pair(nextX, nextY));
				q2.push(make_pair(nextX, nextY));
			}
		}
	}

	for (color = 1; color <= M; color++) {
		q1 = q2;
		size = q2.size();
		rainbowCnt = q2.size();
		oR = 21;
		oC = 21;

		while (!q1.empty()) {
			startX = q1.front().first;
			startY = q1.front().second;
			q1.pop();
			for (int d = 0; d < 4; d++) {
				nextX = startX + dx[d];
				nextY = startY + dy[d];
				if (!inRange(nextX, nextY)) continue;
				else if (map[nextX][nextY] == color && visited[nextX][nextY] == 0) {
					size++;
					visited[nextX][nextY] = 1;
					q1.push(make_pair(nextX, nextY));
					if (oR > nextX) {
						oR = nextX;
						oC = nextY;
					}
					else if (oR == nextX && oC > nextY) {
						oC = nextY;
					}
				}
				else if (map[nextX][nextY] == 0 && visited[nextX][nextY] == 0) {
					size++;
					rainbowCnt++;
					visited[nextX][nextY] = 1;
					q1.push(make_pair(nextX, nextY));
				}
			}
		}
		if (size == rainbowCnt || size < 2) continue;

		if (tmpArr[1] < size) {
			tmpArr[0] = color;
			tmpArr[1] = size;
			tmpArr[2] = rainbowCnt;
			tmpArr[3] = oR;
			tmpArr[4] = oC;
		}
		else if (tmpArr[1] == size && tmpArr[2] < rainbowCnt) {
			tmpArr[0] = color;
			tmpArr[2] = rainbowCnt;
			tmpArr[3] = oR;
			tmpArr[4] = oC;
		}
		else if (tmpArr[1] == size && tmpArr[2] == rainbowCnt && tmpArr[3] < oR) {
			tmpArr[0] = color;
			tmpArr[3] = oR;
			tmpArr[4] = oC;
		}
		else if (tmpArr[1] == size && tmpArr[2] == rainbowCnt && tmpArr[3] == oR && tmpArr[4] < oC) {
			tmpArr[0] = color;
			tmpArr[4] = oC;
		}

	}
	//cout << "해당 무지개 블록에서 가장 큰 블록" << endl;
	//cout << "컬러: " << tmpArr[0] << ", 크기: " << tmpArr[1] << ", 무지개블록수: " << tmpArr[2] << ", 기준블록: (" << tmpArr[3] << ", " << tmpArr[4] << ')' << endl;
	if (tmpArr[0] == 0) return;
	dq.push_back(make_pair(tmpArr[0], make_pair(make_pair(tmpArr[1], tmpArr[2]), make_pair(tmpArr[3], tmpArr[4]))));
}

void find_rainbowBlock() { 
	//겹쳐있는 무지개 블록 제거
	int visited[21][21] = { 0, };
	int size = r.size();
	int startX, startY, nextX, nextY;

	queue <pair <int, int>> q;

	for (int i = 0; i < size; i++) {
		startX = r.front().first;
		startY = r.front().second;
		r.pop_front();
		if (visited[startX][startY] == 1) continue;

		r.push_back(make_pair(startX, startY));
		visited[startX][startY] = 1;
		q.push(make_pair(startX, startY));

		while (!q.empty()) {
			startX = q.front().first;
			startY = q.front().second;
			q.pop();
			for (int d = 0; d < 4; d++) {
				nextX = startX + dx[d];
				nextY = startY + dy[d];
				if (!inRange(nextX, nextY)) continue;
				if (map[nextX][nextY] == 0 && visited[nextX][nextY] == 0) {
					visited[nextX][nextY] = 1;
					q.push(make_pair(nextX, nextY));
				}
			}
		}
	}

}

void find_rainbow() {
	while (!r.empty()) r.pop_front();

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 0) r.push_back(make_pair(i, j));
		}
	}
}

void Solution() {
	int time = 0, score = 0;
	/*
	find_rainbowBlock();
	print();
	while (!r.empty()) {
		//cout << "무지개블록 탐색: (" << r.front().first << ", " << r.front().second <<')' << endl;
		find_large_block(r.front().first, r.front().second);
		r.pop_front();
		//cout << endl;
	}
	sort(dq.begin(), dq.end(), compare);
	remove_block(dq.front().first, dq.front().second.second.first, dq.front().second.second.second);
	score += (dq.front().second.first.first * dq.front().second.first.first);
	while (!dq.empty()) dq.pop_front();
	
	cout << score << endl;
	print_map();
	*/
	//cout << "가장 큰 블록" << endl;
	//cout << "컬러: " << dq.front().first << ", 사이즈: " << dq.front().second.first.first << ", 무지개블록수: " << dq.front().second.first.second << ", 기준블록: (" << dq.front().second.second.first << ", " << dq.front().second.second.second << ')' << endl;
	
	while (1) {
		if (time > 0) find_rainbow(); 
		find_rainbowBlock();
		while (!r.empty()) {
			find_large_block(r.front().first, r.front().second);
			r.pop_front();
		}
		if (dq.size() == 0) break;

		sort(dq.begin(), dq.end(), compare);
		remove_block(dq.front().first, dq.front().second.second.first, dq.front().second.second.second);
		score += (dq.front().second.first.first * dq.front().second.first.first);
		while (!dq.empty()) dq.pop_front();
		//print_map();
		remove_map();
		//print_map();
		rotate_map();
		//print_map();
		remove_map();
		print_map();
		cout << score << endl;
		time++;
	}
	
}

void Input() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0) r.push_back(make_pair(i, j));
		}
	}
}

int main(void) {
	Input();
	Solution();
	//print();
	//find_rainbowBlock();
	//print();
	return 0;
}